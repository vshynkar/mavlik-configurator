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

// show radio version
String MavlinkModem::ati() {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI\r", ATI_DELAY, false);
    response.replace("ATI\r\n", "");
    stopCmdMode();
  }
  return response;
}

// show board type
String MavlinkModem::ati2() {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI2\r", ATI_DELAY, false);
    response.replace("ATI2\r\n", "");
    stopCmdMode();
  }
  return response;
}

// show board frequency
String MavlinkModem::ati3() {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI3\r", ATI_DELAY, false);
    response.replace("ATI3\r\n", "");
    stopCmdMode();
  }
  return response;
}

// show board version
String MavlinkModem::ati4() {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI4\r", ATI_DELAY, false);
    response.replace("ATI4\r\n", "");
    stopCmdMode();
  }
  return response;
}

// display TDM timing report
String MavlinkModem::ati6() {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI6\r", ATI_DELAY, false);
    response.replace("ATI6\r\n", "");
    stopCmdMode();
  }
  return response;
}

// display RSSI signal report
String MavlinkModem::ati7() {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI7\r", ATI_DELAY, false);
    response.replace("ATI7\r\n", "");
    stopCmdMode();
  }
  return response;
}

// ATSn? – display radio parameter number ‘n’
int MavlinkModem::ats(int number) {
  String cmd = "ATS" + String(number) + "?\r";
  String value = runCmd(cmd, 30, false);
  value.replace(cmd, "");
  value.replace("\r\n", "");
  return value.toInt();
}

void MavlinkModem::atsAll(int* rows) {
  String cmd;
  String value;
  for (int i = 0; i < 16; i++) {
    cmd = "ATS" + String(i) + "?\r";
    value = runCmd(cmd, 30, false);
    value.replace(cmd, "");
    value.replace("\r\n", "");
    rows[i] = value.toInt();
  }
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


//void cmdATI5() {
//  ati5Response = runCmd("ATI5\r", 80, false);
//  ati5Response.replace("ATI5\r\n", "");
//  ati5Time = usedTime;
//}

