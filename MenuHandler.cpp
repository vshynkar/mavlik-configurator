#include "MenuHandler.h"

MenuHandler::MenuHandler(Adafruit_PCD8544* d) {
  display = d;
  isFirstRun = true;
  currentMenu = MENU_MAIN;
}

void MenuHandler::pressedKey(int button) {

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
  byte poss = menuPoss[currentMenu];
  return poss;
}

void MenuHandler::showCurrentMenu(void) {
  //  currentMenu = MENU_MAIN;
  //
  //  if (button == BUTTON_ENTER) {
  //    switch (menu0Poss) {
  //      case 0: {
  //          showScrModemInfo(BUTTON_NOP);
  //          return;
  //        }
  //    }
  //  }

  int itemCount = sizeof(menuMain) / LINE_LENGTH;
  //  menu0Poss = menuCursor(menu0Poss, itemCount, button);

  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0, 0);
  display->setTextColor(BLACK);

  for (int i = 0; i < itemCount; i++) {
    if (i == 0) {
      display->setTextColor(WHITE, BLACK);
    }
    for (int j = 0; j < LINE_LENGTH; j++) {
      display->print(menuMain[i][j]);
    }
    if (i == 0) {
      display->setTextColor(BLACK);
    }
  }
  display->display();
}

