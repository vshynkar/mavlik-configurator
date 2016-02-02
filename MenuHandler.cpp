#include "MenuHandler.h"
#include "Keypad.h"
#include "ModemConfigSlot.h"

MenuHandler::MenuHandler(Adafruit_PCD8544* d, ScreenHandler* scr, I2C_eeprom* e) {
  display = d;
  screen = scr;
  ee = e;
  isFirstRun = true;
  isScreenShowing = false;
  currentMenuCode = MENU_MAIN;
  menuDepthIndex = 0;

  for (int i = 0; i < sizeof(menuPoss); i++) {
    menuPoss[i] = 0;
  }
  for (int i = 0; i < sizeof(menuDepthArray); i++) {
    menuDepthArray[i] = 0;
  }
  menuDepthArray[0] = MENU_MAIN;
}

void MenuHandler::pressedKey(byte button) {
  byte screenButton;
  if (!isScreenShowing) {
    switch (button) {
      case BUTTON_UP: {
          if (menuPoss[currentMenuCode] > 0) {
            menuPoss[currentMenuCode]--;
          }
          break;
        }
      case BUTTON_DOWN: {
          int rowsCount = getMenuRows();
          if (menuPoss[currentMenuCode] < rowsCount - 1) {
            menuPoss[currentMenuCode]++;
          }
          break;
        }
      case BUTTON_ENTER: {
          byte mode = getNextMenu();
          if (mode > SRC_START_INDEX) {
            currentScreenCode = mode;
            isScreenShowing = true;
            screen->cleanData();
          } else {
            currentMenuCode = mode;
            menuDepthIndex++;
            menuDepthArray[menuDepthIndex] = mode;
            if (currentMenuCode == MENU_MAIN) {
              menuPoss[currentMenuCode] = 0;
            }
          }
          break;
        }
      case BUTTON_ESC: {
          if (currentMenuCode != MENU_MAIN) {
            menuPoss[currentMenuCode] = 0;
            menuDepthIndex--;
            currentMenuCode = menuDepthArray[menuDepthIndex];
          }
          break;
        }
    }
  } else {
    switch (button) {
      case BUTTON_UP: {
          screenButton = BUTTON_UP;
          break;
        }
      case BUTTON_DOWN: {
          screenButton = BUTTON_DOWN;
          break;
        }
      case BUTTON_ENTER: {
          break;
        }
      case BUTTON_ESC: {
          currentScreenCode = 0;
          isScreenShowing = false;
          screen->cleanData();
          break;
        }
    }
  }
  if (isScreenShowing) {
    screen->showSelectedScreen(currentScreenCode, screenButton);
  } else {
    showCurrentMenu();
  }
}

void MenuHandler::init(void) {

}

void MenuHandler::start(void) {
  if (isFirstRun) {
    isFirstRun = false;
    showCurrentMenu();
  }
}

byte MenuHandler::getNextMenu(void) {
  byte poss = menuPoss[currentMenuCode];

  switch (currentMenuCode) {
    case MENU_MAIN: {
        return menuMainMap[poss];
      }
    case MENU_CONFIG_MODEM: {
        return menuConfigModemMap[poss];
      }
    case MENU_CONFIG_MODEM_MODEM_TO_MEM: {
        return menuConfigModemModemToMemMap[poss];
      }
    case MENU_CONFIG_MODEM_MEM_TO_SCREEN: {
        return menuConfigModemMemToScreenMap[poss];
      }
    case MENU_CONFIG_MODEM_MEM_TO_MODEM: {
        return menuConfigModemMemToModemMap[poss];
      }
    case MENU_CONFIG_SLOTS: {
        return menuConfigSlotsMap[poss];
      }
    case MENU_CONFIG_SLOTS_DEL_ONE: {
        return menuConfigSlotsDelOneMap[poss];
      }
  }

  return MENU_MAIN;
}

// set appropriate menu rows into 'currentMenuRows' array based on menu code from 'currentMenuCode' variable. Return number of rows in array.
int MenuHandler::getMenuRows(void) {
  int itemCount = 0;
  switch (currentMenuCode) {
    case MENU_MAIN: {
        itemCount = readMenuRows(menuMainRowsNew, sizeof(menuMainRowsNew));
        break;
      }
    case MENU_CONFIG_MODEM: {
        itemCount = readMenuRows(menuConfigModemRowsNew, sizeof(menuConfigModemRowsNew));
        break;
      }
    case MENU_CONFIG_MODEM_MODEM_TO_MEM: {
        itemCount = readMenuRows(menuSlotListNew, sizeof(menuSlotListNew));
        updateMenuSlotList();
        break;
      }
    case MENU_CONFIG_MODEM_MEM_TO_SCREEN: {
        itemCount = readMenuRows(menuSlotListNew, sizeof(menuSlotListNew));
        updateMenuSlotList();
        break;
      }
    case MENU_CONFIG_MODEM_MEM_TO_MODEM: {
        itemCount = readMenuRows(menuSlotListNew, sizeof(menuSlotListNew));
        updateMenuSlotList();
        break;
      }
    case MENU_CONFIG_SLOTS: {
        itemCount = readMenuRows(menuConfigSlotsRowsNew, sizeof(menuConfigSlotsRowsNew));
        break;
      }
    case MENU_CONFIG_SLOTS_DEL_ONE: {
        itemCount = readMenuRows(menuSlotListNew, sizeof(menuSlotListNew));
        updateMenuSlotList();
        break;
      }
  }
  return itemCount;
}

int MenuHandler::readMenuRows(const byte menuRows[], int arraySize) {
  uint16_t startAddr = ee->readInt(MENU_UA_BLOCK_ADDR);
  uint8_t value;
//  Serial.println("MENU_UA_BLOCK_ADDR=" + String(startAddr));
//  Serial.println("arraySize=" + String(arraySize));

  for (int i = 0; i < arraySize; i++) {
    for (int j = 0; j < LINE_LENGTH; j++) {
      value = ee->readByte(startAddr + menuRows[i] * LINE_LENGTH + j);
      currentMenuRows[i][j] = value;
//      Serial.print(value, HEX);
//      Serial.print(", ");
    }
//    Serial.println();
  }
  return arraySize;
}

void MenuHandler::updateMenuSlotList(void) {
  for (int i = 0; i < CONFIG_SLOT_COUNT; i++) {
    ModemConfigSlot slot = ModemConfigSlot();
    slot.readMemory(i);
    if (bitRead(slot.statusFlag, CONFIG_BIT_SLOT_USED_MASK) == 0) {
      currentMenuRows[i][2] = '-';
    }
  }
}

void MenuHandler::showCurrentMenu(void) {
  int itemCount = getMenuRows();

  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0, 0);
  display->setTextColor(BLACK);

  for (int i = 0; i < itemCount; i++) {
    if (i == menuPoss[currentMenuCode]) {
      display->setTextColor(WHITE, BLACK);
    }
    for (int j = 0; j < LINE_LENGTH; j++) {
      display->print(currentMenuRows[i][j]);
    }
    if (i == menuPoss[currentMenuCode]) {
      display->setTextColor(BLACK);
    }
  }
  display->display();
}

void MenuHandler::i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
  int rdata = data;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
}

byte MenuHandler::i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

