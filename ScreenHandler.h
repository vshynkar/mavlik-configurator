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

#define SRC_START_INDEX                100
#define SCR_CONFIG_MODEM_TO_MEM        101
#define SCR_CONFIG_MODEM_TO_SCREEN     102
#define SCR_CONFIG_MEM_TO_MODEM        103
#define SCR_CONFIG_MEM_TO_SCREEN       104


class ScreenHandler {
  public:
    ScreenHandler(Adafruit_PCD8544* d, MavlinkModem* m);
    void showSelectedScreen(byte screenCode, byte button);
    void cleanData(void);

  private:
    void showSrcModemToScreen(void);
    void updateOffset(byte button, byte naxValue);
    void printLine(String label, long value);
    Adafruit_PCD8544* display;
    MavlinkModem* modem;
    unsigned int modemConfig[15];
    boolean isDataCached;
    int displayOffset;
};

#endif
