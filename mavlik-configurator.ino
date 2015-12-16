#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "MavlinkModem.h"

// LCD constants
#define PIN_SCE   6
#define PIN_RST   5
#define PIN_DC    4
#define PIN_MOSI  3
#define PIN_SCLK  2

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

// Keypad constant
#define KEYPAD_ROWS   3
#define KEYPAD_COLS   3
#define PUSH_TIMEOUT  20

#define ACTION_UP      2
#define ACTION_DOWN    8
#define ACTION_LEFT    4
#define ACTION_RIGHT   6
#define ACTION_ENTER   5
#define ACTION_ESC     9
#define ACTION_NOP     -1

#define MENU_MAIN           100
#define SCR_MENU_INFO       101

const byte value[KEYPAD_ROWS][KEYPAD_COLS] {
  {7, 8, 9},
  {4, 5, 6},
  {1, 2, 3}
};

int PinOut[KEYPAD_COLS] {9, 8, 7}; // пины выходы
int PinIn[KEYPAD_ROWS] {12, 11, 10}; // пины входа

byte action = ACTION_NOP;
long pushedTime = 0;

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
//Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_DC, PIN_SCE, PIN_RST);

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_MOSI, PIN_DC, PIN_SCE, PIN_RST);

MavlinkModem modem(&Serial);

int menu0Poss = 0;
int currentMenu = MENU_MAIN;

boolean isFirstRun = true;

void setup() {
  initDisplay();
  modem.init(BOUND_RATE_57600);
  initKeypad();
}

void loop() {
  if (isFirstRun) {
    isFirstRun = false;
    showMenuMain();
  }
  
  if (!readKeypad()) {
    delay(10);
    return;
  }
  switch (currentMenu) {
    case MENU_MAIN: {
        showMenuMain();
        break;
      }
    case SCR_MENU_INFO: {
        showScrModemInfo();
        break;
      }
  }
}

void showMenuMain() {
  String items[] = { "  Modem Info ",  "  Modem Info "};
  int itemCount = 2;
  currentMenu = MENU_MAIN;

  if (action == ACTION_ENTER) {
    switch (menu0Poss) {
      case 0: {
          action = ACTION_NOP;
          showScrModemInfo();
          return;
        }
    }
  }

  menu0Poss = menuCursor(menu0Poss, itemCount, action);

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

void showScrModemInfo() {
  currentMenu = SCR_MENU_INFO;
  if (action == ACTION_ESC) {
    action = ACTION_NOP;
    showMenuMain();
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
  if (currentValue < (itemNumber - 1) && action == ACTION_DOWN) {
    result++;
  } else if (currentValue > 0 && action == ACTION_UP) {
    result--;
  }
  return result;
}

void initKeypad() {
  for (int i = 0; i < KEYPAD_COLS; i++) {
    pinMode(PinOut[i], OUTPUT); // инициализируем порты на выход (подают нули на столбцы)
  }

  for (int i = 0; i < KEYPAD_ROWS; i++) {
    pinMode (PinIn[i], INPUT); // инициализируем порты на вход с подтяжкой к плюсу (принимают нули на строках)
    digitalWrite(PinIn[i], HIGH);
  }
}

bool readKeypad() { // создаем функцию для чтения кнопок
  bool isPushed = false;
  for (int i = 1; i <= KEYPAD_COLS; i++) { // цикл, передающий 0 по всем столбцам
    digitalWrite(PinOut[i - 1], LOW); // если i меньше 3 , то отправляем 0 на ножку
    for (int j = 1; j <= KEYPAD_ROWS; j++) { // цикл, принимающих 0 по строкам
      if (digitalRead(PinIn[j - 1]) == LOW) { // если один из указанных портов входа равен 0, то..
        unsigned int wasteTime = millis() - pushedTime;
        if (abs(wasteTime) > PUSH_TIMEOUT) {
          action = value[i - 1][j - 1]; // то b равно значению из двойного массива
          isPushed = true;
          pushedTime = millis();
        }
      }
    }
    digitalWrite(PinOut[i - 1], HIGH); // подаём обратно высокий уровень
  }
  return isPushed;
}

void initDisplay() {
  display.begin();
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
}


