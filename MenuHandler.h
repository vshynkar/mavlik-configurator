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
#include "Configuration.h"


// this number is index in menuPossition array. So the value ust be incremental withous gaps.
#define MENU_COUNT                        12
#define MENU_MAIN                         1
#define MENU_CONFIG_MODEM                 2
#define MENU_CONFIG_MODEM_MODEM_TO_MEM    3
#define MENU_CONFIG_MODEM_MEM_TO_SCREEN   4
#define MENU_CONFIG_MODEM_MEM_TO_MODEM    5
#define MENU_CONFIG_SLOTS                 6
#define MENU_CONFIG_SLOTS_DEL_ONE         7
#define MENU_SECRET_KEY                   8
#define MENU_CONFIGURATIONS               9
#define MENU_CONFIG_LANG                  10
#define MENU_CONFIG_SPEED                 11


#define LINE_LENGTH                       14
#define DISPLAY_ROWS                      6
#define MAX_MENU_DEPTH                    20

// message codes
#define MSG_MODEM_CONFIG                  0
#define MSG_SECRET_KEY                    1
#define MSG_PROFILES                      2
#define MSG_MODEM_TO_MEM                  3
#define MSG_MODEM_TO_SCREEN               4
#define MSG_MEM_TO_MODEM                  5
#define MSG_MEM_TO_SCREEN                 6
#define MSG_SLOT_1                        7
#define MSG_SLOT_2                        8
#define MSG_SLOT_3                        9
#define MSG_SLOT_4                        10
#define MSG_SLOT_5                        11
#define MSG_SLOT_6                        12
#define MSG_DELETE_ALL                    13
#define MSG_DELETE_ONE                    14
#define MSG_CONFIGURATIONS                15
#define MSG_CONFIG_LANG                   16
#define MSG_SERIAL_SPEED                  17
#define MSG_LANGUAGE_UA                   18
#define MSG_LANGUAGE_EN                   19
#define MSG_19200                         20
#define MSG_28800                         21
#define MSG_31250                         22
#define MSG_38400                         23
#define MSG_57600                         24
#define MSG_115200                        25

// menu position is index in this array. It indicates what menu will be next.
const byte menuMainMap[] =                      {MENU_CONFIG_MODEM, MENU_CONFIG_MODEM, MENU_CONFIG_SLOTS, MENU_CONFIGURATIONS};
const byte menuMainRows[] =                     {MSG_MODEM_CONFIG, MSG_SECRET_KEY, MSG_PROFILES, MSG_CONFIGURATIONS};

const byte menuConfigMap[] =                    {MENU_CONFIG_LANG, MENU_CONFIG_SPEED};
const byte menuConfigRows[] =                   {MSG_CONFIG_LANG, MSG_SERIAL_SPEED};

const byte menuConfigLangMap[] =                {SCR_SELECT_UA_LANG, SCR_SELECT_EN_LANG};
const byte menuConfigLangRows[] =               {MSG_LANGUAGE_UA, MSG_LANGUAGE_EN};

const byte menuConfigSerialSpeedMap[] =         {SCR_SET_SERIAL_19200, SCR_SET_SERIAL_28800, SCR_SET_SERIAL_31250, SCR_SET_SERIAL_38400, SCR_SET_SERIAL_57600, SCR_SET_SERIAL_115200};
const byte menuConfigSerialSpeedRows[] =        {MSG_19200, MSG_28800, MSG_31250, MSG_38400, MSG_57600, MSG_115200};

const byte menuConfigModemMap[] =               {MENU_CONFIG_MODEM_MODEM_TO_MEM, SCR_CONFIG_MODEM_TO_SCREEN, MENU_CONFIG_MODEM_MEM_TO_MODEM, MENU_CONFIG_MODEM_MEM_TO_SCREEN};
const byte menuConfigModemRowsNew[] =           {MSG_MODEM_TO_MEM, MSG_MODEM_TO_SCREEN, MSG_MEM_TO_MODEM, MSG_MEM_TO_SCREEN};

const byte menuSlotListNew[] =                  {MSG_SLOT_1, MSG_SLOT_2, MSG_SLOT_3, MSG_SLOT_4, MSG_SLOT_5, MSG_SLOT_6};

const byte menuConfigSlotsMap[] =               {SCR_CONFIG_SLOTS_DEL_ALL, MENU_CONFIG_SLOTS_DEL_ONE};
const byte menuConfigSlotsRowsNew[] =           {MSG_DELETE_ALL, MSG_DELETE_ONE};

const byte menuConfigModemModemToMemMap[] =     {SCR_CONFIG_MODEM_TO_MEM_1,  SCR_CONFIG_MODEM_TO_MEM_2,  SCR_CONFIG_MODEM_TO_MEM_3,  SCR_CONFIG_MODEM_TO_MEM_4,  SCR_CONFIG_MODEM_TO_MEM_5,  SCR_CONFIG_MODEM_TO_MEM_6};
const byte menuConfigModemMemToScreenMap[] =    {SCR_CONFIG_MEM_TO_SCREEN_1, SCR_CONFIG_MEM_TO_SCREEN_2, SCR_CONFIG_MEM_TO_SCREEN_3, SCR_CONFIG_MEM_TO_SCREEN_4, SCR_CONFIG_MEM_TO_SCREEN_5, SCR_CONFIG_MEM_TO_SCREEN_6};
const byte menuConfigModemMemToModemMap[] =     {SCR_CONFIG_MEM_TO_MODEM_1,  SCR_CONFIG_MEM_TO_MODEM_2,  SCR_CONFIG_MEM_TO_MODEM_3,  SCR_CONFIG_MEM_TO_MODEM_4,  SCR_CONFIG_MEM_TO_MODEM_5,  SCR_CONFIG_MEM_TO_MODEM_6};
const byte menuConfigSlotsDelOneMap[] =         {SCR_CONFIG_SLOTS_DEL_ONE_1, SCR_CONFIG_SLOTS_DEL_ONE_2, SCR_CONFIG_SLOTS_DEL_ONE_3, SCR_CONFIG_SLOTS_DEL_ONE_4, SCR_CONFIG_SLOTS_DEL_ONE_5, SCR_CONFIG_SLOTS_DEL_ONE_6};


class MenuHandler {
  public:
    MenuHandler(Adafruit_PCD8544* d, ScreenHandler* scr, Configuration* conf);
    void pressedKey(byte button);
    void start(void);
    void init(void);
    void showCurrentMenu(void);       // print menu rows on display. Menu code in 'currentMenuCode' variable
    void showConfFromModem(void);

  private:
    byte getNextMenu(void);
    int getMenuRows(void);            // set appropriate menu rows into 'currentMenuRows' array based on menu code from 'currentMenuCode' variable. Return number of rows in array.
    void changeCursor(void);
    int readMenuRows(const byte menuRows[], int arraySize);
    void updateMenuSlotList(void);
    Adafruit_PCD8544* display;
    ScreenHandler* screen;
    Configuration* configuration;
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
