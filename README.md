# mavlik-configurator
Program for device to configure Mavlink modems (mainly used with ArduPilot) without PC

Mavlink modem AT commands:
* http://copter.ardupilot.com/wiki/common-3dr-radio-advanced-configuration-and-technical-information/

Copied and customized next projects' code to add support of Ukrainian language:
* https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library
* https://github.com/adafruit/Adafruit-GFX-Library


Device prototype

![alt tag](https://github.com/vshynkar/mavlik-configurator/blob/master/maket.png)






Features:
* use matrix keypad, nokia 3310 display (via software SPI) and mavlink modem via hardware Serial interface;
* save modem configurations into profiles into EEPROM. Ability to read and view;
* create user interface and use 4 buttons to navigate (up, down, enter, escape);
* Ukrainian user interface;

Secon development phase, items TODO:
* use hardware SPI to communicate with nokia display;
* create custom keypad using input shift register 74HC165 to save arduino pins. Use interruptions for key events;
* add ability to configure the device. Save configurations into EEPROM;
* add English user interface and ability to swith between Ukrainian and English. Save text messages into external EEPROM;
* use special logic level converter chip instead of voltage divitor based on resistors for nokia display;


* 1 - GRND
* 2 - VCC
* 3 - QH
* 4 - CLK
* 5 - SH/LD
* 6 - INT
