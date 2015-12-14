
// Supported bound rate 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600 and 115200
#define BOUND_RATE 57600


class MavlinkModem {
  public:
    void init();

  private:
    void startCmdMode();
    void stopCmdMode();
};

