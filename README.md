# mavlik-configurator
Program for device to configure Mavlink modems (mainly used with ArduPilot) without PC

Mavlink modem AT commands:
* http://copter.ardupilot.com/wiki/common-3dr-radio-advanced-configuration-and-technical-information/

Copied and customized next projects' code to add support of Ukrainian language:
* https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library
* https://github.com/adafruit/Adafruit-GFX-Library


Device prototype

![alt tag](https://github.com/vshynkar/mavlik-configurator/blob/master/maket.png)






Особливості:
* робота з матричною клавіатурою, нокіа дисплеєем (через софтварний SPI) і хардварним Serial портом
* робота з eeprom для зберігання і читання профілів налаштувань модема
* організація інтерфейсного меню з управліням 4-ма клавішами (up, down, enter, back)
* усе меню УКРАЇНСЬКОЮ мовою

У другій фазі планується:
* повішати дисплей на хардварний SPI інтерфейс
* замінити матричну клавіатуру на набір звичайних кнопок із вхідним здвиговим регістром
* в меню додати розділ для збереження ряду налаштувань
* підключити зовнішню eeprom мікросхему
* додати англійську мову і переключення між мовами. Тексти для меню зберігати у зовнішній eeprom
*  дисплей підключити через мікросхему конвертора рівнів 5 - 3,3 вольта  і позбутися дільників напруги на резисторах
* використати стабілізатор на 3,3 вольта замість 4-х послідовних діодів для живлення дисплея

Є плани і на третю фазу. Третьою фазою буде закінчений автономний девайс.
Кому цікаво по технічних нюансах, нюансах реалізації чи ще щось по проекту, то питайте.



1 - GRND
2 - VCC
3 - QH
4 - CLK
5 - SH/LD
6 - INT
