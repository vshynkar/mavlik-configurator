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
}

byte Keypad::read(void) { // создаем функцию для чтения кнопок
  byte button = BUTTON_NOP;

  long bitVal;
  BYTES_VAL_T bytesVal = 0;

  /* Trigger a parallel Load to latch the state of the data lines,
  */
  digitalWrite(ploadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(ploadPin, HIGH);

  /* Loop to read each bit value from the serial out line
     of the SN74HC165N.
  */
  for (int i = 0; i < DATA_WIDTH; i++) {
    bitVal = digitalRead(dataPin);

    /* Set the corresponding bit in bytesVal.
    */
    bytesVal |= (bitVal << ((DATA_WIDTH - 1) - i));

    /* Pulse the Clock (rising edge shifts the next bit).
    */
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockPin, LOW);
  }

    for (int i = 0; i < DATA_WIDTH; i++) {
    Serial.print("  Pin-");
    Serial.print(i);
    Serial.print(": ");

    if ((bytesVal >> i) & 1) {
      Serial.print("HIGH");
    } else {
      Serial.print("LOW");
    }
    Serial.print("\r\n");
  }
  return button;
}
