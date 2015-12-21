#ifndef _MENU_HANDLER_H
#define _MENU_HANDLER_H

#include <avr/pgmspace.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "ScreenHandler.h"

// this number is index in menuPossition array. So the value ust be incremental withous gaps.
#define MENU_MAIN            1
#define MENU_CONFIG_MODEM    2
#define MENU_SECRET_KEY      3

#define LINE_LENGTH          14
#define DISPLAY_ROWS         6

const char menuMainRows[][LINE_LENGTH] = {
  {0xCB, 0xF0, 0xEF, 0xF6, 0xE9, 0xE1, 0x20, 0xEE, 0xF0, 0xE3, 0xE4, 0xEe, 0xDe, 0x20},    // Конфіг модема
  {0xD2, 0xE4, 0xEC, 0xF2, 0xE4, 0xF4, 0xEF, 0xE8, 0xEB, 0x20, 0xEc, 0xED, 0xFD, 0xF9}     // Секретний ключ
  };

const char menuConfigModemRows[][LINE_LENGTH] = {
  {0xCD, 0xF0, 0xE3, 0xE4, 0xEE, 0xBC, 0xD0, 0xDE, 0xEE, 0xBA, 0xFE, 0xF4, 0xFC, 0x20},    // Модем->Память
  {0xCD, 0xF0, 0xE3, 0xE4, 0xEE, 0xBC, 0xC3, 0xEC, 0xF2, 0xDE, 0xEF, 0x00, 0x00, 0x20},    // Модем->Екран
  {0xD0, 0xDE, 0xEE, 0xBA, 0xFE, 0xF4, 0xFC, 0xBC, 0xCD, 0xF0, 0xE3, 0xE4, 0xEE, 0x20},    // Память->Модем
  {0xD0, 0xDE, 0xEE, 0xBA, 0xFE, 0xF4, 0xFC, 0xBC, 0xC3, 0xEC, 0xF2, 0xDE, 0xEF, 0x20}     // Память->Екран
  };

// menu position is index in this array. It indicates what menu will be next.
const byte menuMainMap[] = {MENU_CONFIG_MODEM, MENU_CONFIG_MODEM};
const byte menuConfigModemMap[] = {SCR_CONFIG_MODEM_TO_MEM, SCR_CONFIG_MODEM_TO_SCREEN, SCR_CONFIG_MEM_TO_MODEM, SCR_CONFIG_MEM_TO_SCREEN};

class MenuHandler {
  public:
    MenuHandler(Adafruit_PCD8544* d, ScreenHandler* scr);
    void pressedKey(byte button);
    void start(void);
    void init(void);
    void showCurrentMenu(void);       // print menu rows on display. Menu code in 'currentMenuCode' variable
    void showConfFromModem(void);
  
  private:
    byte getNextMenu(void);
    int getMenuRows(void);            // set appropriate menu rows into 'currentMenuRows' array based on menu code from 'currentMenuCode' variable. Return number of rows in array.
    void changeCursor(void);
    Adafruit_PCD8544* display;
    ScreenHandler* screen;
    boolean isFirstRun;
    boolean isScreenShowing;
    byte currentMenuCode;
    byte currentScreenCode;
    byte menuPoss[3] {0, 0, 0};        // Menu code is index here. Every value is current index in appropriate menu.
    char currentMenuRows[DISPLAY_ROWS][LINE_LENGTH];
};

#endif
