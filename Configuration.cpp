#include "Configuration.h"

Configuration::Configuration(I2C_eeprom* e) {
  ee = e;
}

void Configuration::init(void) {
  englishMenuBlockAddr = ee->readInt(MENU_EN_BLOCK_ADDR);
  ukrainianMenuBlockAddr = ee->readInt(MENU_UA_BLOCK_ADDR);
  configBlockAddr = ee->readInt(CONFIG_BLOCK_ADDR);
  memoryStructureVersion = ee->readInt(MEM_STRUCTURE_VERSION);

  currentLanguageAddr = ee->readInt(configBlockAddr + LANGUAGE_ADDR_OFFSET);
}

void Configuration::readScreenMessage(byte messageCode, char bufferArray[], byte count) {
  uint8_t value;
  uint16_t startAddr = currentLanguageAddr;
  for (int i = 0; i < count; i++) {
    value = ee->readByte(startAddr + messageCode * count + i);
    bufferArray[i]= (char) value;
  }
}

void Configuration::setCurrentLangUa(void) {
  currentLanguageAddr = ukrainianMenuBlockAddr;
  ee->writeInt(configBlockAddr + LANGUAGE_ADDR_OFFSET, currentLanguageAddr);
}

void Configuration::setCurrentLangEn(void) {
  currentLanguageAddr = englishMenuBlockAddr;
  ee->writeInt(configBlockAddr + LANGUAGE_ADDR_OFFSET, currentLanguageAddr);
}
