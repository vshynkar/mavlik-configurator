#include "glcdfont.c"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "MavlinkModem.h"
#include "KeypadMatrix.h"
#include "MenuHandler.h"

// LCD constants
#define PIN_SCE   6
#define PIN_RST   5
#define PIN_DC    4
#define PIN_MOSI  3
#define PIN_SCLK  2

#define SCR_MENU_INFO       101

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
//Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_DC, PIN_SCE, PIN_RST);

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_MOSI, PIN_DC, PIN_SCE, PIN_RST);
MavlinkModem modem(&Serial);
KeypadMatrix keypad(12, 11, 10, 9, 8, 7);
MenuHandler menuHandler = MenuHandler(&display);

int menu0Poss = 0;

void setup() {
  initDisplay();
  modem.init(BOUND_RATE_57600);
  keypad.init();
  menuHandler.init();
}

void loop() {
  menuHandler.start();
  byte button = keypad.read();
  if (button != BUTTON_NOP) {
    menuHandler.pressedKey(button);
  } else {
    delay(20);
  }
}
//
//void showScrModemInfo(byte button) {
//  currentMenu = SCR_MENU_INFO;
//  if (button == BUTTON_ESC) {
//    showMenuMain(BUTTON_NOP);
//    return;
//  }
//
//  String response = modem.ati();
//
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setCursor(0, 0);
//  display.setTextColor(BLACK);
//  display.println("Radio ver:");
//  display.println(response);
//  display.display();
//}

void initDisplay() {
  display.begin();
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
}


