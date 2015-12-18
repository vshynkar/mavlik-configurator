#include <stdlib.h>
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

// this number is index in menuPossition array. So the value ust be incremental withous gaps.
#define MENU_MAIN            1
#define MENU_CONFIG_MODEM    2
#define MENU_SECRET_KEY      3

#define LINE_LENGTH          14

const char menuMain[][LINE_LENGTH] = {
  {0xCC, 0xF1, 0xF0, 0xF7, 0xEA, 0xE2, 0x00, 0xEF, 0xF1, 0xE4, 0xE5, 0xEF, 0xDF, 0x00},    // Конфіг модема
  {0xD3, 0xE5, 0xED, 0xF3, 0xE5, 0xF5, 0xF0, 0xE9, 0xEC, 0x00, 0xED, 0xEE, 0xFE, 0xFA}     // Секретний ключ
  };

// menu position is index in this array. It indicates what menu will be next.
const byte menuMainMap[] {MENU_CONFIG_MODEM, MENU_SECRET_KEY};


class MenuHandler {
  public:
    MenuHandler(Adafruit_PCD8544* d);
    void pressedKey(int button);
    void start(void);
    void init(void);
    void showCurrentMenu(void);
  
  private:
    Adafruit_PCD8544* display;
    boolean isFirstRun;
    byte currentMenu;
    byte getNextMenu(void);
    byte menuPoss[3] {0, 0, 0};        // Menu code is index here. every value is current index in appropriate menu.
//    *char getMenuRows(void);
};

