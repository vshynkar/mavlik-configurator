# mavlik-configurator
Program for device to configure Mavlink modems (mainly used with ArduPilot) without PC

Mavlink modem AT commands:
* http://copter.ardupilot.com/wiki/common-3dr-radio-advanced-configuration-and-technical-information/

Copied and customized next projects' code to add support of Ukrainian language:
* https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library
* https://github.com/adafruit/Adafruit-GFX-Library


Device prototype

![alt tag](https://github.com/vshynkar/mavlik-configurator/blob/master/image/maket.png)






Features:
* use matrix keypad, nokia 3310 display (via software SPI) and mavlink modem via hardware Serial interface;
* save modem configurations into profiles into EEPROM. Ability to read and view;
* create user interface and use 4 buttons to navigate (up, down, enter, escape);
* Ukrainian user interface;

Secon development phase, items TODO:
* use hardware SPI to communicate with nokia display (done);
* create custom keypad using input shift register 74HC165 to save arduino pins. Use interruptions for key events (done);
* add ability to configure the device. Save configurations into EEPROM (added serial port speed select);
* add English user interface and ability to swith between Ukrainian and English. Save text messages into external EEPROM (done);
* use special logic level converter chip instead of voltage divitor based on resistors for nokia display (not needed);
* use 5V to 3.3V converter for nokia display;
* save memory slots into external eeprom;

LCD connector pins:

* 1 - VCC 3.3V
* 2 - GND
* 3 - SCE
* 4 - RST
* 5 - D/C
* 6 - DN<MOSI>
* 7 - SCLK
* 8 - LED

Keypad connector pins:

* 1 - GND
* 2 - VCC
* 3 - Q7 inverted (7 pin on chip)
* 4 - SCK (2 pin on chip)
* 5 - PL (1 pin on chip)
* 6 - INT (connect to interruption pin on arduino)
