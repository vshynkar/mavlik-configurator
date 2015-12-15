#include <stdlib.h>
//#include <avr/io.h>
//#include <stdint.h>
//#include <avr/common.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include "MavlinkModem.h"

MavlinkModem::MavlinkModem(HardwareSerial* s) {
  serial = s;
}

void MavlinkModem::init(int boundRate) {
  serial->begin(boundRate);
}

bool MavlinkModem::startCmdMode() {
  String response = runCmd("+++", 1200, true);
  return response.equals("OK");
}

void MavlinkModem::stopCmdMode() {
  runCmd("ATO\r", 30, false);
}

String MavlinkModem::ati() {
  String response = runCmd("ATI\r", 30, false);
  response.replace("ATI\r\n", "");
  return response;
}

String MavlinkModem::runCmd(String cmd, int timeout, bool checkCR) {
  String response = "";
  serial->print(cmd);

  unsigned long firstReadTime = millis();
  unsigned long lastReadTime = 0;
  while (true) {
    if (serial->available() > 0) {
      char symbol = serial->read();
      if (checkCR && symbol == '\r') {
        operationUsedTime = millis() - firstReadTime;
        break;
      } else {
        response += String(symbol);
        lastReadTime = millis();
      }
    } else if ((millis() - firstReadTime) > timeout) {
      if (checkCR) {
        operationUsedTime = millis() - firstReadTime;
      } else {
        operationUsedTime = lastReadTime - firstReadTime;
      }
      break;
    }
  }
  return response;
}

unsigned int MavlinkModem::getOperationUsedTime() {
  return operationUsedTime;
}

