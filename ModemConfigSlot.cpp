#include "ModemConfigSlot.h"
#include <EEPROM.h>

void ModemConfigSlot::readMemory(byte slotNumber) {
  int address = startAddress(slotNumber);
  int offset = 0;

  statusFlag = EEPROM.read(address + offset);
  offset++;

  for (int i = 0; i < sizeof(slotName); i++) {
    slotName[i] = EEPROM.read(address + offset + i);
  }
  offset += sizeof(slotName);

  reserved1 = readInt(address + offset);
  offset += 2;

  reserved2 = readInt(address + offset);
  offset += 2;

  serialSpeed = readInt(address + offset);
  offset += 2;

  airSpeed = readInt(address + offset);
  offset += 2;

  netId = readInt(address + offset);
  offset += 2;

  txPower = readInt(address + offset);
  offset += 2;

  ecc = readInt(address + offset);
  offset += 2;

  mavlink = readInt(address + offset);
  offset += 2;

  oppresend = readInt(address + offset);
  offset += 2;

  minFreq = readInt(address + offset);
  offset += 2;

  maxFreq = readInt(address + offset);
  offset += 2;

  numberChannels = readInt(address + offset);
  offset += 2;

  dutyCyrcle = readInt(address + offset);
  offset += 2;

  lbtRssi = readInt(address + offset);
  offset += 2;

  manchester = readInt(address + offset);
  offset += 2;

  rtscts = readInt(address + offset);
  offset += 2;

  maxWindow = readInt(address + offset);
}

void ModemConfigSlot::writeMemory(byte slotNumber) {
  int address = startAddress(slotNumber);
  int offset = 0;

  EEPROM.update(address + offset, statusFlag);
  offset++;

  for (int i = 0; i < sizeof(slotName); i++) {
    EEPROM.update(address + offset + i, slotName[i]);
  }
  offset += sizeof(slotName);

  writeInt(address + offset, reserved1);
  offset += 2;

  writeInt(address + offset, reserved2);
  offset += 2;

  writeInt(address + offset, serialSpeed);
  offset += 2;

  writeInt(address + offset, airSpeed);
  offset += 2;

  writeInt(address + offset, netId);
  offset += 2;

  writeInt(address + offset, txPower);
  offset += 2;

  writeInt(address + offset, ecc);
  offset += 2;

  writeInt(address + offset, mavlink);
  offset += 2;

  writeInt(address + offset, oppresend);
  offset += 2;

  writeInt(address + offset, minFreq);
  offset += 2;

  writeInt(address + offset, maxFreq);
  offset += 2;

  writeInt(address + offset, numberChannels);
  offset += 2;

  writeInt(address + offset, dutyCyrcle);
  offset += 2;

  writeInt(address + offset, lbtRssi);
  offset += 2;

  writeInt(address + offset, manchester);
  offset += 2;

  writeInt(address + offset, rtscts);
  offset += 2;

  writeInt(address + offset, maxWindow);
}

int ModemConfigSlot::startAddress(byte slotNumber) {
  return (slotNumber + 1) * CONFIG_SLOT_SIZE + CONFIG_SLOT_START;
}

int ModemConfigSlot::readInt(int address) {
  byte lowByte = EEPROM.read(address);
  byte highByte = EEPROM.read(address + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void ModemConfigSlot::writeInt(int address, int value) {
  byte lowByte = ((value >> 0) & 0xFF);
  byte highByte = ((value >> 8) & 0xFF);

  EEPROM.update(address, lowByte);
  EEPROM.update(address + 1, highByte);
}

void ModemConfigSlot::deleteSlot(byte slotNumber) {
  int address = startAddress(slotNumber);
  for (int i = 0; i < CONFIG_SLOT_SIZE; i++) {
    EEPROM.update(address + i, 0x00);
  }
}

void ModemConfigSlot::convertIn(int rows[]) {
  serialSpeed =    rows[0];
  airSpeed =       rows[1];
  netId =          rows[2];
  txPower =        rows[3];
  ecc =            rows[4];
  mavlink =        rows[5];
  oppresend =      rows[6];
  minFreq =        rows[7];
  maxFreq =        rows[8];
  numberChannels = rows[9];
  dutyCyrcle =     rows[10];
  lbtRssi =        rows[11];
  manchester =     rows[12];
  rtscts =         rows[13];
  maxWindow =      rows[14];

}

void ModemConfigSlot::convertOut(int rows[]) {
  rows[0] = serialSpeed;
  rows[1] = airSpeed;
  rows[2] = netId;
  rows[3] = txPower;
  rows[4] = ecc;
  rows[5] = mavlink;
  rows[6] = oppresend;
  rows[7] = minFreq;
  rows[8] = maxFreq;
  rows[9] = numberChannels;
  rows[10] = dutyCyrcle;
  rows[11] = lbtRssi;
  rows[12] = manchester;
  rows[13] = rtscts;
  rows[14] = maxWindow;
}

