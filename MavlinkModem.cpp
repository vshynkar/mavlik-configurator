#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MavlinkModem.h"

MavlinkModem::MavlinkModem(HardwareSerial *s) {
  serial = s;
}

bool MavlinkModem::startCmdMode(void) {
  String response = runCmd("+++", 1200, true);
  return response.equals("OK");
}

void MavlinkModem::stopCmdMode(void) {
  runCmd("ATO\r", ATI_DELAY, false);
}

// show radio version
String MavlinkModem::ati(void) {
  //  String response = runCmd("+++", 1200, true);
  //  runCmd("ATO\r", ATI_DELAY, false);
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI\r", ATI_DELAY, false);
    response.replace("ATI\r\n", "");
    stopCmdMode();
  }
  return response;
}

// show board type
String MavlinkModem::ati2(void) {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI2\r", ATI_DELAY, false);
    response.replace("ATI2\r\n", "");
    stopCmdMode();
  }
  return response;
}

// show board frequency
String MavlinkModem::ati3(void) {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI3\r", ATI_DELAY, false);
    response.replace("ATI3\r\n", "");
    stopCmdMode();
  }
  return response;
}

// show board version
String MavlinkModem::ati4(void) {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI4\r", ATI_DELAY, false);
    response.replace("ATI4\r\n", "");
    stopCmdMode();
  }
  return response;
}

// display TDM timing report
String MavlinkModem::ati6(void) {
  String response = "";
  if (startCmdMode()) {
    response = runCmd("ATI6\r", ATI_DELAY, false);
    response.replace("ATI6\r\n", "");
    stopCmdMode();
  }
  return response;
}

// display RSSI signal report
String MavlinkModem::ati7(void) {
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
  int result;
  if (startCmdMode()) {
    String cmd = "ATS" + String(number) + "?\r";
    String value = runCmd(cmd, ATI_DELAY, false);
    value.replace(cmd, "");
    value.replace("\r\n", "");

    if (number == 8 || number == 9) {
    char tarray[10];
      value.toCharArray(tarray, sizeof(tarray));
      long lValue = atol(tarray);
      result = lValue / 1000;
    } else {
      result = value.toInt();
    }
    stopCmdMode();
  }
  return result;
}

// ATSn=X – set radio parameter number ‘n’ to ‘X’
void MavlinkModem::ats(int number, int p_value) {
  long regValue;
  if (startCmdMode()) {
    if (number == 8 || number == 9) {
      regValue = long(p_value) *1000;
    } else {
      regValue = p_value;
    }
    String cmd = "ATS" + String(number) + "=" + String(regValue) + "\r";
    runCmd(cmd, ATI_DELAY, false);
    runCmd("AT&W\r", ATI_DELAY, false);
    stopCmdMode();
  }
}

void MavlinkModem::readAtsAll(int rows[]) {
  if (startCmdMode()) {
    String cmd;
    String value;
    for (int i = 1; i < 16; i++) {
      cmd = "ATS" + String(i) + "?\r";
      value = runCmd(cmd, ATI_DELAY, false);
      value.replace(cmd, "");
      value.replace("\r\n", "");

      if (i == 8 || i == 9) {
      char tarray[10];
        value.toCharArray(tarray, sizeof(tarray));
        long lValue = atol(tarray);
        rows[i-1] = lValue / 1000;
      } else {
        rows[i-1] = value.toInt();
      }
    }
    stopCmdMode();
  }
}

void MavlinkModem::writeAtsAll(int rows[]) {
  if (startCmdMode()) {
    String cmd;
    long value;
    for (int i = 1; i < 16; i++) {
      if (i == 8 || i == 9) {
        value = long(rows[i-1]) * 1000;
      } else {
        value = long(rows[i-1]);
      }
      cmd = "ATS" + String(i) + "=" + value + "\r";
      runCmd(cmd, ATI_DELAY, false);
    }
    runCmd("AT&W\r", ATI_DELAY, false);
    stopCmdMode();
  }
}

String MavlinkModem::runCmd(String cmd, int timeout, bool checkCR) {
  String response = "";
  Serial.print(cmd);

  unsigned long firstReadTime = millis();
  unsigned long lastReadTime = 0;
  while (true) {
    if (Serial.available() > 0) {
      char symbol = Serial.read();
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

unsigned int MavlinkModem::getOperationUsedTime(void) {
  return operationUsedTime;
}


//void cmdATI5() {
//  ati5Response = runCmd("ATI5\r", 80, false);
//  ati5Response.replace("ATI5\r\n", "");
//  ati5Time = usedTime;
//}

