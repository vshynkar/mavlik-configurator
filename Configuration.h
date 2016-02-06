#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "I2C_eeprom.h"

#define MENU_EN_BLOCK_ADDR      0x00
#define MENU_UA_BLOCK_ADDR      0x02
#define CONFIG_BLOCK_ADDR       0x04
#define MEM_STRUCTURE_VERSION   0x06
#define RESERVED_2_ADDR         0x08
#define RESERVED_3_ADDR         0x0A
#define RESERVED_4_ADDR         0x0C
#define RESERVED_5_ADDR         0x0E
#define RESERVED_6_ADDR         0x10
#define RESERVED_7_ADDR         0x12

#define LANGUAGE_ADDR_OFFSET    0x00



class Configuration {
  public:
    uint16_t englishMenuBlockAddr;
    uint16_t ukrainianMenuBlockAddr;
    uint16_t configBlockAddr;
    uint16_t memoryStructureVersion;
  
    uint16_t currentLanguageAddr;

    Configuration(I2C_eeprom* e);
    void init(void);
    void readScreenMessage(byte messageCode, char bufferArray[], byte count);
    void setCurrentLangUa(void);
    void setCurrentLangEn(void);

  private:
    I2C_eeprom* ee;
};

#endif
