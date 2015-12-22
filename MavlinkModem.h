#ifndef _MAVLINK_MODEM_H
#define _MAVLINK_MODEM_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define BOUND_RATE_14400    14400
#define BOUND_RATE_19200    19200
#define BOUND_RATE_28800    28800
#define BOUND_RATE_31250    31250
#define BOUND_RATE_38400    38400
#define BOUND_RATE_57600    57600
#define BOUND_RATE_115200   115200

#define ATI_DELAY           30


class MavlinkModem {
  public:
    MavlinkModem(HardwareSerial *s);
    unsigned int getOperationUsedTime(void);

    String ati(void);
    String ati2(void);
    String ati3(void);
    String ati4(void);
    String ati6(void);
    String ati7(void);
    int ats(int number);
    void ats(int number, int value);
    void readAtsAll(int rows[]);
    void writeAtsAll(int rows[]);
    void reboot(void);
    void resetToDefault(void);

  private:
    HardwareSerial* serial;
    unsigned int operationUsedTime;
    
    bool startCmdMode(void);
    void stopCmdMode(void);
    String runCmd(String cmd, int timeout, bool checkCR);
};


#endif
