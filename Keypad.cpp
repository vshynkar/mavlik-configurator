#include "Keypad.h"

Keypad::Keypad(byte data, byte clk, byte pload) {
  dataPin = data;
  clockPin = clk;
  ploadPin = pload;
}

void Keypad::init(void) {
  pinMode(ploadPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(ploadPin, HIGH);

  read();
}

byte Keypad::read(void) { // создаем функцию для чтения кнопок
  byte button = BUTTON_NOP;
  
  if (millis() - pushedTime < PUSH_TIMEOUT) {
    return button;
  }

  pushedTime = millis();

  digitalWrite(ploadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(ploadPin, HIGH);

  if (readKeypadPin() == LOW) {
    button = BUTTON_ENTER;
  }
  if (readKeypadPin() == LOW) {
    button = BUTTON_LEFT;
  }
  if (readKeypadPin() == LOW) {
    button = BUTTON_ESC;
  }
  if (readKeypadPin() == LOW) {
    button = BUTTON_UP;
  }
  readKeypadPin();
  readKeypadPin();
  if (readKeypadPin() == LOW) {
    button = BUTTON_RIGHT;
  }
  if (readKeypadPin() == LOW) {
    button = BUTTON_DOWN;
  }
  return button;
}

byte Keypad::readKeypadPin() {
  byte value;
  value = digitalRead(dataPin);
  digitalWrite(clockPin, HIGH);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(clockPin, LOW);
  return value;
}

