#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "MavlinkModem.h"
#include "KeypadMatrix.h"

// LCD constants
#define PIN_SCE   6
#define PIN_RST   5
#define PIN_DC    4
#define PIN_MOSI  3
#define PIN_SCLK  2

#define MENU_MAIN           100
#define SCR_MENU_INFO       101

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
//Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_DC, PIN_SCE, PIN_RST);

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_MOSI, PIN_DC, PIN_SCE, PIN_RST);
MavlinkModem modem(&Serial);
KeypadMatrix keypad(12, 11, 10, 9, 8, 7);

int menu0Poss = 0;
int currentMenu = MENU_MAIN;

boolean isFirstRun = true;

void setup() {
  initDisplay();
  modem.init(BOUND_RATE_57600);
  keypad.init();
}

void loop() {
  if (isFirstRun) {
    isFirstRun = false;
    showMenuMain(BUTTON_NOP);
  }

  byte button = keypad.read();
  if (button == BUTTON_NOP) {
    delay(10);
    return;
  }
  switch (currentMenu) {
    case MENU_MAIN: {
        showMenuMain(button);
        break;
      }
    case SCR_MENU_INFO: {
        showScrModemInfo(button);
        break;
      }
  }
}

void showMenuMain(byte button) {
  String items[] = { "  Modem Info ",  "  Modem Info "};
  int itemCount = 2;
  currentMenu = MENU_MAIN;

  if (button == BUTTON_ENTER) {
    switch (menu0Poss) {
      case 0: {
          showScrModemInfo(BUTTON_NOP);
          return;
        }
    }
  }

  menu0Poss = menuCursor(menu0Poss, itemCount, button);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(BLACK);

  for (int i = 0; i < itemCount; i++) {
    if (i == menu0Poss) {
      display.setTextColor(WHITE, BLACK);
    }
    display.println(items[i]);
    if (i == menu0Poss) {
      display.setTextColor(BLACK);
    }
  }
  display.display();
}

void showScrModemInfo(byte button) {
  currentMenu = SCR_MENU_INFO;
  if (button == BUTTON_ESC) {
    showMenuMain(BUTTON_NOP);
    return;
  }

  String response = modem.ati();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  display.println("Radio ver:");
  display.println(response);
  display.display();
}

int menuCursor(int currentValue, int itemNumber, byte action) {
  int result = currentValue;
  if (currentValue < (itemNumber - 1) && action == BUTTON_DOWN) {
    result++;
  } else if (currentValue > 0 && action == BUTTON_UP) {
    result--;
  }
  return result;
}

void initDisplay() {
  display.begin();
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
}


