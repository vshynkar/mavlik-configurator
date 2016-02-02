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
#include "I2C_eeprom.h"


#define MEM_DATA_ADDR           0x14

#define MENU_EN_BLOCK_ADDR      0x00
#define MENU_UA_BLOCK_ADDR      0x02
#define CONFIG_BLOCK_ADDR       0x04
#define MEM_STRUCTURE_VERSION   0x06
#define RESERVED_2_ADDR         0x08
#define RESERVED_3_ADDR         0x0A
#define RESERVED_4_ADDR         0x0C
#define RESERVED_5_ADDR         0x0E
#define RESERVED_6_ADDR         0x10
#define RESERVED_7_ADDR         0x12


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
const byte menuMainRowsNew[] = {
  0,    // Конфіг модема
  1,    // Секретний ключ
  2     // Профілі
};

const byte menuConfigModemMap[] =               {MENU_CONFIG_MODEM_MODEM_TO_MEM, SCR_CONFIG_MODEM_TO_SCREEN, MENU_CONFIG_MODEM_MEM_TO_MODEM, MENU_CONFIG_MODEM_MEM_TO_SCREEN};
const byte menuConfigModemRowsNew[] = {
  3,    // Модем->Память
  4,    // Модем->Екран
  5,    // Память->Модем
  6     // Память->Екран
};

const byte menuSlotListNew[] = {
  7,    // Профіль 1
  8,    // Профіль 2
  9,    // Профіль 3
  10,   // Профіль 4
  11,   // Профіль 5
  12    // Профіль 6
};

const byte menuConfigSlotsMap[] =               {SCR_CONFIG_SLOTS_DEL_ALL, MENU_CONFIG_SLOTS_DEL_ONE};
const byte menuConfigSlotsRowsNew[] = {
  13,    // Видалити усі
  14     // Видалити один
};

const byte menuConfigModemModemToMemMap[] =    {SCR_CONFIG_MODEM_TO_MEM_1,  SCR_CONFIG_MODEM_TO_MEM_2,  SCR_CONFIG_MODEM_TO_MEM_3,  SCR_CONFIG_MODEM_TO_MEM_4,  SCR_CONFIG_MODEM_TO_MEM_5,  SCR_CONFIG_MODEM_TO_MEM_6};
const byte menuConfigModemMemToScreenMap[] =   {SCR_CONFIG_MEM_TO_SCREEN_1, SCR_CONFIG_MEM_TO_SCREEN_2, SCR_CONFIG_MEM_TO_SCREEN_3, SCR_CONFIG_MEM_TO_SCREEN_4, SCR_CONFIG_MEM_TO_SCREEN_5, SCR_CONFIG_MEM_TO_SCREEN_6};
const byte menuConfigModemMemToModemMap[] =    {SCR_CONFIG_MEM_TO_MODEM_1,  SCR_CONFIG_MEM_TO_MODEM_2,  SCR_CONFIG_MEM_TO_MODEM_3,  SCR_CONFIG_MEM_TO_MODEM_4,  SCR_CONFIG_MEM_TO_MODEM_5,  SCR_CONFIG_MEM_TO_MODEM_6};
const byte menuConfigSlotsDelOneMap[] =        {SCR_CONFIG_SLOTS_DEL_ONE_1, SCR_CONFIG_SLOTS_DEL_ONE_2, SCR_CONFIG_SLOTS_DEL_ONE_3, SCR_CONFIG_SLOTS_DEL_ONE_4, SCR_CONFIG_SLOTS_DEL_ONE_5, SCR_CONFIG_SLOTS_DEL_ONE_6};


class MenuHandler {
  public:
    MenuHandler(Adafruit_PCD8544* d, ScreenHandler* scr, I2C_eeprom* e);
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
    void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data );
    byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress );
    Adafruit_PCD8544* display;
    ScreenHandler* screen;
    I2C_eeprom* ee;
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
