#ifndef _SCREEN_HANDLER_H
#define _SCREEN_HANDLER_H


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "MavlinkModem.h"
#include "ModemConfigSlot.h"

#define SRC_START_INDEX                100
#define SCR_CONFIG_MODEM_TO_MEM_1      101
#define SCR_CONFIG_MODEM_TO_MEM_2      102
#define SCR_CONFIG_MODEM_TO_MEM_3      103
#define SCR_CONFIG_MODEM_TO_MEM_4      104
#define SCR_CONFIG_MODEM_TO_MEM_5      105
#define SCR_CONFIG_MODEM_TO_MEM_6      106
#define SCR_CONFIG_MODEM_TO_SCREEN     107
#define SCR_CONFIG_MEM_TO_MODEM_1      108
#define SCR_CONFIG_MEM_TO_MODEM_2      109
#define SCR_CONFIG_MEM_TO_MODEM_3      110
#define SCR_CONFIG_MEM_TO_MODEM_4      111
#define SCR_CONFIG_MEM_TO_MODEM_5      112
#define SCR_CONFIG_MEM_TO_MODEM_6      113
#define SCR_CONFIG_MEM_TO_SCREEN_1     114
#define SCR_CONFIG_MEM_TO_SCREEN_2     115
#define SCR_CONFIG_MEM_TO_SCREEN_3     116
#define SCR_CONFIG_MEM_TO_SCREEN_4     117
#define SCR_CONFIG_MEM_TO_SCREEN_5     118
#define SCR_CONFIG_MEM_TO_SCREEN_6     119
#define SCR_CONFIG_MEM_TO_SCREEN_7     120
#define SCR_CONFIG_SLOTS_DEL_ALL       121
#define SCR_CONFIG_SLOTS_DEL_ONE_1     122
#define SCR_CONFIG_SLOTS_DEL_ONE_2     123
#define SCR_CONFIG_SLOTS_DEL_ONE_3     124
#define SCR_CONFIG_SLOTS_DEL_ONE_4     125
#define SCR_CONFIG_SLOTS_DEL_ONE_5     126
#define SCR_CONFIG_SLOTS_DEL_ONE_6     127

#define LINE_LENGTH                    14

const char message_1[LINE_LENGTH] = {0x20, 0x20, 0xC6, 0xDF, 0xE4, 0xF2, 0xE4, 0xE6, 0xE4, 0xEF, 0xF0, '!',   0x20, 0x20};    // Збережено
const char message_2[LINE_LENGTH] = {0x20, 0x20, 0xC6, 0xF9, 0xE8, 0xF4, 0xF5, 0xE0, 0xDE, 0xEF, 0xEF, 0xFE,  0x20, 0x20};    // Зчитування
const char message_3[LINE_LENGTH] = {0x20, 0x20, 0x20, 0xBF, 0xE8, 0xE3, 0xDE, 0xED, 0xE4, 0xEF, 0xF0, 0x20,  0x20, 0x20};    // Видалено

class ScreenHandler {
  public:
    ScreenHandler(Adafruit_PCD8544* d, MavlinkModem* m);
    void showSelectedScreen(byte screenCode, byte button);
    void cleanData(void);

  private:
    void showSrcModemToScreen(void);
    void showSrcModemToMem(byte slotNumber);
    void showSrcMemToModem(byte slotNumber);
    void showSrcMemToScreen(byte slotNumber);
    void showSrcSlotDelOne(byte slotNumber);
    void showSrcSlotDelAll(void);
    void updateOffset(byte button, byte maxValue);
    void printLine(String label, long value);
    void showScrMessage(const char msg[]);
    void showOnScreen(void);
    Adafruit_PCD8544* display;
    MavlinkModem* modem;
    int modemConfig[15];
    boolean isDataCached;
    int displayOffset;
};

#endif
