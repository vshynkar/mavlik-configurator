#include "glcdfont.c"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "MavlinkModem.h"
#include "KeypadMatrix.h"
#include "MenuHandler.h"
#include "ScreenHandler.h"

// LCD constants
#define PIN_SCE   7
#define PIN_RST   6
#define PIN_DC    5
#define PIN_MOSI  4
#define PIN_SCLK  3

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
//Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_DC, PIN_SCE, PIN_RST);

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_MOSI, PIN_DC, PIN_SCE, PIN_RST);
MavlinkModem modem(&Serial);
KeypadMatrix keypad = KeypadMatrix(13, 12, 11, 10, 9, 8);
ScreenHandler screenHandler = ScreenHandler(&display, &modem);
MenuHandler menuHandler = MenuHandler(&display, &screenHandler);

String initResponse;
String atiResponse;
int atiTime, usedTime, initTime;

void setup() {
  initDisplay();
  Serial.begin(BOUND_RATE_57600);
  keypad.init();
  menuHandler.init();
}

void loop() {
  menuHandler.start();
  byte button = keypad.read();
  if (button == BUTTON_UP || button == BUTTON_DOWN || button == BUTTON_ENTER || button == BUTTON_ESC) {
    menuHandler.pressedKey(button);
  } else {
    delay(20);
  }
}

void initDisplay() {
  display.begin();
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
}


