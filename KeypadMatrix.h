#ifndef _KEYPAD_MATRIX_H
#define _KEYPAD_MATRIX_H

#include <stdlib.h>
#include <Arduino.h>

#define BUTTON_NOP  -1
#define BUTTON_0    0
#define BUTTON_1    1
#define BUTTON_2    2
#define BUTTON_3    3
#define BUTTON_4    4
#define BUTTON_5    5
#define BUTTON_6    6
#define BUTTON_7    7
#define BUTTON_8    8
#define BUTTON_9    9

#define BUTTON_UP        2
#define BUTTON_DOWN      8
#define BUTTON_LEFT      4
#define BUTTON_RIGHT     6
#define BUTTON_ENTER     5
#define BUTTON_ESC       9

#define KEYPAD_ROWS      3
#define KEYPAD_COLS      3
#define PUSH_TIMEOUT     200


class KeypadMatrix {
  public:
    KeypadMatrix(byte in1, byte in2, byte in3, byte out1, byte out2, byte out3);
    void init(void);
    byte read(void);

  private:
    const byte keypad[KEYPAD_ROWS][KEYPAD_COLS] {
      {BUTTON_7, BUTTON_8, BUTTON_9},
      {BUTTON_4, BUTTON_5, BUTTON_6},
      {BUTTON_1, BUTTON_2, BUTTON_3}
    };
    byte pinOut[KEYPAD_COLS] {9, 8, 7}; // пины выходы
    byte pinIn[KEYPAD_ROWS] {12, 11, 10}; // пины входа
    unsigned int pushedTime;
};

#endif
