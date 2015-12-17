
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
    MavlinkModem(HardwareSerial* s);
    void init(int boundRate);
    unsigned int getOperationUsedTime();

    String ati();
    String ati2();
    String ati3();
    String ati4();
    String ati6();
    String ati7();
    int ats(int number);
    void atsAll(int* rows);
    void ats(int number, int value);
    void reboot();
    void flushToEeprom();
    void resetToDefault();

  private:
    HardwareSerial* serial;
    unsigned int operationUsedTime;
    
    bool startCmdMode();
    void stopCmdMode();
    String runCmd(String cmd, int timeout, bool checkCR);
};
