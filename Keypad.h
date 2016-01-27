#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <stdlib.h>
#include <Arduino.h>

#define BYTES_VAL_T unsigned int

#define PULSE_WIDTH_USEC   5
#define POLL_DELAY_MSEC    1
#define DATA_WIDTH         8

#define BUTTON_NOP  -1
#define BUTTON_UP        2
#define BUTTON_DOWN      8
#define BUTTON_LEFT      4
#define BUTTON_RIGHT     6
#define BUTTON_ENTER     5
#define BUTTON_ESC       9

#define PUSH_TIMEOUT     200


class Keypad {
  public:
    Keypad(byte data, byte clk, byte pload);
    void init(void);
    byte read(void);

  private:
    BYTES_VAL_T pushedTime;
    byte dataPin;
    byte clockPin;
    byte ploadPin;
    byte readKeypadPin();
};

#endif
