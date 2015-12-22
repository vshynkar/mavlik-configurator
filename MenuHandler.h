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
#define MENU_COUNT                        8
#define MENU_MAIN                         1
#define MENU_CONFIG_MODEM                 2
#define MENU_CONFIG_MODEM_MODEM_TO_MEM    3
#define MENU_CONFIG_MODEM_MEM_TO_SCREEN   4
#define MENU_CONFIG_MODEM_MEM_TO_MODEM    5
#define MENU_CONFIG_SLOTS                 6
#define MENU_CONFIG_SLOTS_DEL_ONE         7
#define MENU_SECRET_KEY                   8

#define LINE_LENGTH          14
#define DISPLAY_ROWS         6
#define MAX_MENU_DEPTH       20

// menu position is index in this array. It indicates what menu will be next.
const byte menuMainMap[] =               {MENU_CONFIG_MODEM, MENU_CONFIG_MODEM, MENU_CONFIG_SLOTS};
const char menuMainRows[][LINE_LENGTH] = {
  {0xCB, 0xF0, 0xEF, 0xF6, 0xE9, 0xE1, 0x20, 0xEE, 0xF0, 0xE3, 0xE4, 0xEE, 0xDE, 0x20},    // Конфіг модема
  {0xD2, 0xE4, 0xEC, 0xF2, 0xE4, 0xF4, 0xEF, 0xE8, 0xEB, 0x20, 0xEc, 0xED, 0xFD, 0xF9},    // Секретний ключ
  {0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xE9, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}     // Профілі
};

const byte menuConfigModemMap[] =               {MENU_CONFIG_MODEM_MODEM_TO_MEM, SCR_CONFIG_MODEM_TO_SCREEN, MENU_CONFIG_MODEM_MEM_TO_MODEM, MENU_CONFIG_MODEM_MEM_TO_SCREEN};
const char menuConfigModemRows[][LINE_LENGTH] = {
  {0xCD, 0xF0, 0xE3, 0xE4, 0xEE, 0xBC, 0xD0, 0xDE, 0xEE, 0xBA, 0xFE, 0xF4, 0xFC, 0x20},    // Модем->Память
  {0xCD, 0xF0, 0xE3, 0xE4, 0xEE, 0xBC, 0xC3, 0xEC, 0xF2, 0xDE, 0xEF, 0x00, 0x00, 0x20},    // Модем->Екран
  {0xD0, 0xDE, 0xEE, 0xBA, 0xFE, 0xF4, 0xFC, 0xBC, 0xCD, 0xF0, 0xE3, 0xE4, 0xEE, 0x20},    // Память->Модем
  {0xD0, 0xDE, 0xEE, 0xBA, 0xFE, 0xF4, 0xFC, 0xBC, 0xC3, 0xEC, 0xF2, 0xDE, 0xEF, 0x20}     // Память->Екран
};

const char menuSlotList[][LINE_LENGTH] = {
  {0x20, 0x20, 0x20, 0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xFC, 0x20, '1',  0x20, 0x20},    // Профіль 1
  {0x20, 0x20, 0x20, 0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xFC, 0x20, '2',  0x20, 0x20},    // Профіль 2
  {0x20, 0x20, 0x20, 0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xFC, 0x20, '3',  0x20, 0x20},    // Профіль 3
  {0x20, 0x20, 0x20, 0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xFC, 0x20, '4',  0x20, 0x20},    // Профіль 4
  {0x20, 0x20, 0x20, 0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xFC, 0x20, '5',  0x20, 0x20},    // Профіль 5
  {0x20, 0x20, 0x20, 0xD0, 0xF2, 0xF0, 0xF6, 0xE9, 0xED, 0xFC, 0x20, '6',  0x20, 0x20}     // Профіль 6
};

const byte menuConfigSlotsMap[] =               {SCR_CONFIG_SLOTS_DEL_ALL, MENU_CONFIG_SLOTS_DEL_ONE};
const char menuConfigSlotsRows[][LINE_LENGTH] = {
  {0xBF, 0xE8, 0xE3, 0xDE, 0xED, 0xE8, 0xF4, 0xE8, 0x20, 0xF5, 0xF3, 0xE9, 0x20, 0x20},    // Видалити усі
  {0xBF, 0xE8, 0xE3, 0xDE, 0xED, 0xE8, 0xF4, 0xE8, 0x20, 0xF0, 0xE3, 0xE8, 0xEF, 0x20}     // Видалити один
};

const byte menuConfigModemModemToMemMap[] =    {SCR_CONFIG_MODEM_TO_MEM_1,  SCR_CONFIG_MODEM_TO_MEM_2,  SCR_CONFIG_MODEM_TO_MEM_3,  SCR_CONFIG_MODEM_TO_MEM_4,  SCR_CONFIG_MODEM_TO_MEM_5,  SCR_CONFIG_MODEM_TO_MEM_6};
const byte menuConfigModemMemToScreenMap[] =   {SCR_CONFIG_MEM_TO_SCREEN_1, SCR_CONFIG_MEM_TO_SCREEN_2, SCR_CONFIG_MEM_TO_SCREEN_3, SCR_CONFIG_MEM_TO_SCREEN_4, SCR_CONFIG_MEM_TO_SCREEN_5, SCR_CONFIG_MEM_TO_SCREEN_6};
const byte menuConfigModemMemToModemMap[] =    {SCR_CONFIG_MEM_TO_MODEM_1,  SCR_CONFIG_MEM_TO_MODEM_2,  SCR_CONFIG_MEM_TO_MODEM_3,  SCR_CONFIG_MEM_TO_MODEM_4,  SCR_CONFIG_MEM_TO_MODEM_5,  SCR_CONFIG_MEM_TO_MODEM_6};
const byte menuConfigSlotsDelOneMap[] =        {SCR_CONFIG_SLOTS_DEL_ONE_1, SCR_CONFIG_SLOTS_DEL_ONE_2, SCR_CONFIG_SLOTS_DEL_ONE_3, SCR_CONFIG_SLOTS_DEL_ONE_4, SCR_CONFIG_SLOTS_DEL_ONE_5, SCR_CONFIG_SLOTS_DEL_ONE_6};


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
    int copyMenuRows(const char menuRows[][LINE_LENGTH], int arraySize);
    void updateMenuSlotList(void);
    Adafruit_PCD8544* display;
    ScreenHandler* screen;
    boolean isFirstRun;
    boolean isScreenShowing;
    byte currentMenuCode;
    byte menuDepthArray[MAX_MENU_DEPTH];
    byte menuDepthIndex;
    byte currentScreenCode;
    byte menuPoss[MENU_COUNT];        // Menu code is index here. Every value is current index in appropriate menu.
    char currentMenuRows[DISPLAY_ROWS][LINE_LENGTH];
};

#endif
