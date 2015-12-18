#include <stdlib.h>
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

// this number is index in menuPossition array. So the value ust be incremental withous gaps.
#define MENU_MAIN            1
#define MENU_CONFIG_MODEM    2
#define MENU_SECRET_KEY      3

#define LINE_LENGTH          14
#define DISPLAY_ROWS         6

const char menuMainRows[][LINE_LENGTH] = {
  {0xCC, 0xF1, 0xF0, 0xF7, 0xEA, 0xE2, 0x00, 0xEF, 0xF1, 0xE4, 0xE5, 0xEF, 0xDF, 0x00},    // Конфіг модема
  {0xD3, 0xE5, 0xED, 0xF3, 0xE5, 0xF5, 0xF0, 0xE9, 0xEC, 0x00, 0xED, 0xEE, 0xFE, 0xFA}     // Секретний ключ
  };

const char menuConfigModemRows[][LINE_LENGTH] = {
  {0xCE, 0xF1, 0xE4, 0xE5, 0xEF, 0xAF, 0xD1, 0xDF, 0xEF, 0xFF, 0xF5, 0xFD, 0x00, 0x00},    // Модем->Память
  {0xCE, 0xF1, 0xE4, 0xE5, 0xEF, 0xAF, 0xC4, 0xED, 0xF3, 0xDF, 0xF0, 0x00, 0x00, 0x00},    // Модем->Екран
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    // Память->Модем
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}     // Память->Екран
  };

// menu position is index in this array. It indicates what menu will be next.
const byte menuMainMap[] = {MENU_CONFIG_MODEM, MENU_CONFIG_MODEM};
const byte menuConfigModemMap[] = {MENU_MAIN, MENU_MAIN, MENU_MAIN, MENU_MAIN};

class MenuHandler {
  public:
    MenuHandler(Adafruit_PCD8544* d);
    void pressedKey(byte button);
    void start(void);
    void init(void);
    void showCurrentMenu(void);       // print menu rows on display. Menu code in 'currentMenuCode' variable
  
  private:
    byte getNextMenu(void);
    int getMenuRows(void);            // set appropriate menu rows into 'currentMenuRows' array based on menu code from 'currentMenuCode' variable. Return number of rows in array.
    void changeCursor(void);
    Adafruit_PCD8544* display;
    boolean isFirstRun;
    byte currentMenuCode;
    byte menuPoss[3] {0, 0, 0};        // Menu code is index here. Every value is current index in appropriate menu.
    char currentMenuRows[DISPLAY_ROWS][LINE_LENGTH];
};

