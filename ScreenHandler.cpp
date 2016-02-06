#include "ScreenHandler.h"
#include "Adafruit_PCD8544.h"
#include "MavlinkModem.h"
#include "Keypad.h"

ScreenHandler::ScreenHandler(Adafruit_PCD8544* d, MavlinkModem* m, Configuration* conf) {
  display = d;
  modem = m;
  configuration = conf;

  isDataCached = false;
  displayOffset = 0;
}

void ScreenHandler::cleanData(void) {
  isDataCached = false;
  displayOffset = 0;
}


void ScreenHandler::showSelectedScreen(byte screenCode, byte button) {
  switch (screenCode) {
    case SCR_CONFIG_MODEM_TO_MEM_1: {
        showSrcModemToMem(0);
        break;
      }
    case SCR_CONFIG_MODEM_TO_MEM_2: {
        showSrcModemToMem(1);
        break;
      }
    case SCR_CONFIG_MODEM_TO_MEM_3: {
        showSrcModemToMem(2);
        break;
      }
    case SCR_CONFIG_MODEM_TO_MEM_4: {
        showSrcModemToMem(3);
        break;
      }
    case SCR_CONFIG_MODEM_TO_MEM_5: {
        showSrcModemToMem(4);
        break;
      }
    case SCR_CONFIG_MODEM_TO_MEM_6: {
        showSrcModemToMem(5);
        break;
      }
    case SCR_CONFIG_MODEM_TO_SCREEN: {
        updateOffset(button, 9);
        showSrcModemToScreen();
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM_1: {
        showSrcMemToModem(0);
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM_2: {
        showSrcMemToModem(1);
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM_3: {
        showSrcMemToModem(2);
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM_4: {
        showSrcMemToModem(3);
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM_5: {
        showSrcMemToModem(4);
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM_6: {
        showSrcMemToModem(5);
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN_1: {
        updateOffset(button, 9);
        showSrcMemToScreen(0);
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN_2: {
        updateOffset(button, 9);
        showSrcMemToScreen(1);
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN_3: {
        updateOffset(button, 9);
        showSrcMemToScreen(2);
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN_4: {
        updateOffset(button, 9);
        showSrcMemToScreen(3);
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN_5: {
        updateOffset(button, 9);
        showSrcMemToScreen(4);
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN_6: {
        updateOffset(button, 9);
        showSrcMemToScreen(5);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ONE_1: {
        showSrcSlotDelOne(0);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ONE_2: {
        showSrcSlotDelOne(1);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ONE_3: {
        showSrcSlotDelOne(2);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ONE_4: {
        showSrcSlotDelOne(3);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ONE_5: {
        showSrcSlotDelOne(4);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ONE_6: {
        showSrcSlotDelOne(5);
        break;
      }
    case SCR_CONFIG_SLOTS_DEL_ALL: {
        showSrcSlotDelAll();
        break;
      }
    case SCR_SELECT_UA_LANG: {
        showSelectUaLang();
        break;
      }
    case SCR_SELECT_EN_LANG: {
        showSelectEnLang();
        break;
      }
    case SCR_SET_SERIAL_19200: {
        showSelectSerialSpeed(19200);
        break;
      }
    case SCR_SET_SERIAL_28800: {
        showSelectSerialSpeed(28800);
        break;
      }
    case SCR_SET_SERIAL_31250: {
        showSelectSerialSpeed(31250);
        break;
      }
    case SCR_SET_SERIAL_38400: {
        showSelectSerialSpeed(38400);
        break;
      }
    case SCR_SET_SERIAL_57600: {
        showSelectSerialSpeed(57600);
        break;
      }
    case SCR_SET_SERIAL_115200: {
        showSelectSerialSpeed(115200);
        break;
      }
  }
}

void ScreenHandler::showSrcSlotDelOne(byte slotNumber) {
  ModemConfigSlot slot = ModemConfigSlot();
  slot.deleteSlot(slotNumber);
  showScrMessage(MSG_DELETED);
}

void ScreenHandler::showSrcSlotDelAll(void) {
  ModemConfigSlot slot = ModemConfigSlot();
  for (int i = 0; i < 6; i++) {
    slot.deleteSlot(i);
  }
  showScrMessage(MSG_DELETED);
}

void ScreenHandler::updateOffset(byte button, byte maxValue) {
  switch (button) {
    case BUTTON_UP: {
        if (displayOffset > 0) {
          displayOffset--;
        }
        break;
      }
    case BUTTON_DOWN: {
        if (displayOffset < maxValue) {
          displayOffset++;
        }
      }
  }
}

void ScreenHandler::showSrcModemToMem(byte slotNumber) {
  if (!isDataCached) {
    showScrMessage(MSG_READING);
    modem->readAtsAll(modemConfig);
    isDataCached = true;
  }

  ModemConfigSlot slot = ModemConfigSlot();
  slot.convertIn(modemConfig);
  bitWrite(slot.statusFlag, CONFIG_BIT_SLOT_USED_MASK, 1);
  slot.writeMemory(slotNumber);

  showScrMessage(MSG_SAVED);
}

void ScreenHandler::showSrcMemToModem(byte slotNumber) {
  if (!isDataCached) {
    showScrMessage(MSG_READING);

    ModemConfigSlot slot = ModemConfigSlot();
    slot.readMemory(slotNumber);
    slot.convertOut(modemConfig);

    isDataCached = true;
  }

  modem->writeAtsAll(modemConfig);
  showScrMessage(MSG_SAVED);
}

void ScreenHandler::showSrcModemToScreen(void) {
  if (!isDataCached) {
    showScrMessage(MSG_READING);
    modem->readAtsAll(modemConfig);
    isDataCached = true;
  }
  showOnScreen();
}

void ScreenHandler::showSrcMemToScreen(byte slotNumber) {
  if (!isDataCached) {
    showScrMessage(MSG_READING);

    ModemConfigSlot slot = ModemConfigSlot();
    slot.readMemory(slotNumber);
    slot.convertOut(modemConfig);

    isDataCached = true;
  }
  showOnScreen();
}

void ScreenHandler::showOnScreen(void) {
  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0, 0);
  display->setTextColor(BLACK);

  if (displayOffset < 1) {
    printLine("PORT_SPEED=", long(modemConfig[0]));
  }
  if (displayOffset < 2) {
    printLine("AIR_SPEED=", long(modemConfig[1]));
  }
  if (displayOffset < 3) {
    printLine("NETID=", long(modemConfig[2]));
  }
  if (displayOffset < 4) {
    printLine("TXPOWER=", long(modemConfig[3]));
  }
  if (displayOffset < 5) {
    printLine("ECC=", long(modemConfig[4]));
  }
  if (displayOffset < 6) {
    printLine("MAVLINK=", long(modemConfig[5]));
  }
  if (displayOffset < 7) {
    printLine("OPPRESEND=", long(modemConfig[6]));
  }
  if (displayOffset < 8) {
    printLine("MIN_FRQ=", long(modemConfig[7]) * 1000);
  }
  if (displayOffset < 9) {
    printLine("MAX_FRQ=", long(modemConfig[8]) * 1000);
  }
  if (displayOffset < 10) {
    printLine("NUM_CHNLS=", long(modemConfig[9]));
    printLine("DUTY_CYCLE=", long(modemConfig[10]));
    printLine("LBT_RSSI=", long(modemConfig[11]));
    printLine("MANCHESTER=", long(modemConfig[12]));
    printLine("RTSCTS=", long(modemConfig[13]));
    printLine("MAX_WINDOW=", long(modemConfig[14]));
  }
  display->display();
}

void ScreenHandler::showSelectUaLang() {
  configuration->setCurrentLangUa();
  showScrMessage(MSG_SAVED);
}

void ScreenHandler::showSelectEnLang() {
  configuration->setCurrentLangEn();
  showScrMessage(MSG_SAVED);
}

void ScreenHandler::showSelectSerialSpeed(uint32_t serialSpeed) {
  configuration->setCurrentSerialSpeed(serialSpeed);
  showScrMessage(MSG_SAVED);
}

void ScreenHandler::showScrMessage(byte messageCode) {
  char bufferArray[LINE_LENGTH];
  configuration->readScreenMessage(messageCode, bufferArray, LINE_LENGTH);

  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0, 0);
  display->setTextColor(BLACK);

  display->println();
  display->println();
  for (int i = 0; i < LINE_LENGTH; i++) {
    display->print(bufferArray[i]);
  }

  display->display();
}

void ScreenHandler::printLine(String label, long value) {
  char row[14];
  label += String(value);

  int strLength = label.length() + 1;

  char strArray[strLength];
  label.toCharArray(strArray, strLength);

  for (int i = 0; i < LINE_LENGTH; i++)  {
    if (i < strLength) {
      row[i] = strArray[i];
    } else {
      row[i] = 0x20;
    }
  }

  for (int i = 0; i < LINE_LENGTH; i++) {
    display->print(row[i]);
  }
}

