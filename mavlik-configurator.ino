#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MavlinkModem.h>

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

// Mavlink Modem constants

// Supported bound rate 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600 and 115200
#define BOUND_RATE 57600

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

unsigned int usedTime = 0;

bool isInit = false;

String initResponse = "";
String atiResponse = "";
String ati2Response = "";
String ati3Response = "";
String ati4Response = "";
String ati5Response = "";
String ati6Response = "";
String ati7Response = "";

String ats0Response = "";

int initTime = 0;
int atiTime = 0;
int ati2Time = 0;
int ati3Time = 0;
int ati4Time = 0;
int ati5Time = 0;
int ati6Time = 0;
int ati7Time = 0;

int ats0Time = 0;

int ats[16];

int menu0Poss = 0;
int currentMenu = MENU_MAIN;

boolean isFirstRun = true;

void setup() {
  initDisplay();
  initSerial();
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

  atiResponse = "";
  if (initConfigModem()) {
    cmdATI();
    cmdATO();
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  display.println("Radio ver:");
  display.println(atiResponse);
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

void initSerial() {
  Serial.begin(BOUND_RATE);
}

bool initConfigModem() {
  initResponse = runCmd("+++", 1200, true);
  initTime = usedTime;
  return initResponse.equals("OK");
}

void cmdATI() {
  atiResponse = runCmd("ATI\r", 30, false);
  atiResponse.replace("ATI\r\n", "");
  atiTime = usedTime;
}

void cmdATI2() {
  ati2Response = runCmd("ATI2\r", 30, false);
  ati2Response.replace("ATI2\r\n", "");
  ati2Time = usedTime;
}

void cmdATI3() {
  ati3Response = runCmd("ATI3\r", 30, false);
  ati3Response.replace("ATI3\r\n", "");
  ati3Time = usedTime;
}

void cmdATI4() {
  ati4Response = runCmd("ATI4\r", 30, false);
  ati4Response.replace("ATI4\r\n", "");
  ati4Time = usedTime;
}

void cmdATI5() {
  ati5Response = runCmd("ATI5\r", 80, false);
  ati5Response.replace("ATI5\r\n", "");
  ati5Time = usedTime;
}

void cmdATI6() {
  ati6Response = runCmd("ATI6\r", 30, false);
  ati6Response.replace("ATI6\r\n", "");
  ati6Time = usedTime;
}

void cmdATI7() {
  ati7Response = runCmd("ATI7\r", 30, false);
  ati7Response.replace("ATI7\r\n", "");
  ati7Time = usedTime;
}

void cmdATS() {
  String value = "";
  String cmd = "";
  for (int i = 0; i < 16; i++) {
    cmd = "ATS" + String(i) + "?\r";
    value = runCmd(cmd, 30, false);
    value.replace(cmd, "");
    value.replace("\r\n", "");
    ats[i] = value.toInt();
  }
}

void cmdATO() {
  runCmd("ATO\r", 30, false);
}

String runCmd(String cmd, int timeout, bool checkCR) {
  String response = "";
  Serial.print(cmd);

  unsigned long firstReadTime = millis();
  unsigned long lastReadTime = 0;
  while (true) {
    if (Serial.available() > 0) {
      char symbol = Serial.read();
      if (checkCR && symbol == '\r') {
        usedTime = millis() - firstReadTime;
        break;
      } else {
        response += String(symbol);
        lastReadTime = millis();
      }
    } else if ((millis() - firstReadTime) > timeout) {
      if (checkCR) {
        usedTime = millis() - firstReadTime;
      } else {
        usedTime = lastReadTime - firstReadTime;
      }
      break;
    }
  }
  return response;
}
