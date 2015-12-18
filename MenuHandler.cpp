#include "MenuHandler.h"
#include "KeypadMatrix.h"

MenuHandler::MenuHandler(Adafruit_PCD8544* d) {
  display = d;
  isFirstRun = true;
  currentMenuCode = MENU_MAIN;
}

void MenuHandler::pressedKey(byte button) {
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
        currentMenuCode = getNextMenu();
        if (currentMenuCode == MENU_MAIN) {
          menuPoss[currentMenuCode] = 0;
        }
        break;
      }
  }
  showCurrentMenu();
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
  }
  
  return MENU_MAIN;
}

// set appropriate menu rows into 'currentMenuRows' array based on menu code from 'currentMenuCode' variable. Return number of rows in array.
int MenuHandler::getMenuRows(void) {
  int itemCount = 0;
  switch (currentMenuCode) {
    case MENU_MAIN: {
        itemCount = sizeof(menuMainRows) / LINE_LENGTH;
        for (int i = 0; i < itemCount; i++) {
          for (int j = 0; j < LINE_LENGTH; j++) {
            currentMenuRows[i][j] = menuMainRows[i][j];
          }
        }
        break;
      }
    case MENU_CONFIG_MODEM: {
        itemCount = sizeof(menuConfigModemRows) / LINE_LENGTH;
        for (int i = 0; i < itemCount; i++) {
          for (int j = 0; j < LINE_LENGTH; j++) {
            currentMenuRows[i][j] = menuConfigModemRows[i][j];
          }
        }
      break;
    }
  }
  return itemCount;
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

