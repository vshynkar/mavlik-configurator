#ifndef _MODEM_CONFIG_SLOT_H
#define _MODEM_CONFIG_SLOT_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


#define CONFIG_SLOT_COUNT   6
#define CONFIG_SLOT_SIZE    49    // in bytes
#define CONFIG_SLOT_START   64    // address of first byte

#define CONFIG_BIT_SLOT_USED_MASK      1


class ModemConfigSlot {
  public:
    void readMemory(byte slotNumber);       // from 0 to 5
    void writeMemory(byte slotNumber);      // from 0 to 5
    void convertIn(int rows[]);
    void convertOut(int rows[]);
    void deleteSlot(byte slotNumber);
  
    byte statusFlag;
    char slotName[14];
    int reserved1;
    int reserved2;
    int serialSpeed;
    int airSpeed;
    int netId;
    int txPower;
    int ecc;
    int mavlink;
    int oppresend;
    int minFreq;
    int maxFreq;
    int numberChannels;
    int dutyCyrcle;
    int lbtRssi;
    int manchester;
    int rtscts;
    int maxWindow;

  private:
    int startAddress(byte slotNumber);
    int readInt(int address);
    void writeInt(int address, int value);
};

#endif
