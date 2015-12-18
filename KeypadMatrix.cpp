

#include "KeypadMatrix.h"

KeypadMatrix::KeypadMatrix(byte in1, byte in2, byte in3, byte out1, byte out2, byte out3) {
  pinIn[0] = in1;
  pinIn[1] = in2;
  pinIn[2] = in3;
  pinOut[0] = out1;
  pinOut[1] = out2;
  pinOut[2] = out3;
}

void KeypadMatrix::init(void) {
  for (int i = 0; i < KEYPAD_COLS; i++) {
    pinMode(pinOut[i], OUTPUT); // инициализируем порты на выход (подают нули на столбцы)
  }

  for (int i = 0; i < KEYPAD_ROWS; i++) {
    pinMode (pinIn[i], INPUT); // инициализируем порты на вход с подтяжкой к плюсу (принимают нули на строках)
    digitalWrite(pinIn[i], HIGH);
  }
}

byte KeypadMatrix::read(void) { // создаем функцию для чтения кнопок
  byte button = BUTTON_NOP;
  for (int i = 1; i <= KEYPAD_COLS; i++) { // цикл, передающий 0 по всем столбцам
    digitalWrite(pinOut[i - 1], LOW); // если i меньше 3 , то отправляем 0 на ножку
    for (int j = 1; j <= KEYPAD_ROWS; j++) { // цикл, принимающих 0 по строкам
      if (digitalRead(pinIn[j - 1]) == LOW) { // если один из указанных портов входа равен 0, то..
        unsigned int wasteTime = millis() - pushedTime;
        if (abs(wasteTime) > PUSH_TIMEOUT) {
          button = keypad[i - 1][j - 1]; // то b равно значению из двойного массива
          pushedTime = millis();
        }
      }
    }
    digitalWrite(pinOut[i - 1], HIGH); // подаём обратно высокий уровень
  }
  return button;
}
