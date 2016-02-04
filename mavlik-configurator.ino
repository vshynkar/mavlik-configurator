#include "glcdfont.c"
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "MavlinkModem.h"
#include "Keypad.h"
#include "MenuHandler.h"
#include "ScreenHandler.h"
#include "I2C_eeprom.h"

// LCD constants
#define PIN_SCE   7
#define PIN_RST   8
#define PIN_DC    9
//#define PIN_MOSI  4
//#define PIN_SCLK  3

// Keypad pins
#define DATA_PIN   5
#define CLOCK_PIN  4
#define PLOAD_PIN  3
#define INT_PIN    2


// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!
Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_DC, PIN_SCE, PIN_RST);

//Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_MOSI, PIN_DC, PIN_SCE, PIN_RST);
I2C_eeprom i2cEeprom = I2C_eeprom(0x50);
MavlinkModem modem(&Serial);
ScreenHandler screenHandler = ScreenHandler(&display, &modem);
MenuHandler menuHandler = MenuHandler(&display, &screenHandler, &i2cEeprom);
Keypad keypad = Keypad(DATA_PIN, CLOCK_PIN, PLOAD_PIN);

volatile byte pressedButton;

void setup() {
  initDisplay();
  Serial.begin(BOUND_RATE_57600);
  keypad.init();
  menuHandler.init();
  attachInterrupt(INT_PIN - 2, getKeypadData, RISING);
}

void loop() {
  menuHandler.start();
  if (pressedButton == BUTTON_UP || pressedButton == BUTTON_DOWN || pressedButton == BUTTON_ENTER || pressedButton == BUTTON_ESC) {
    menuHandler.pressedKey(pressedButton);
    pressedButton = BUTTON_NOP;
  }
}

void getKeypadData() {
  pressedButton = keypad.read();
}

void initDisplay() {
  display.begin();
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
}


