#include "ScreenHandler.h"
#include "Adafruit_PCD8544.h"
#include "MavlinkModem.h"
#include "KeypadMatrix.h"

ScreenHandler::ScreenHandler(Adafruit_PCD8544* d, MavlinkModem* m) {
  display = d;
  modem = m;
  isDataCached = false;
  displayOffset = 0;
}

void ScreenHandler::cleanData(void) {
  isDataCached = 0;
}


void ScreenHandler::showSelectedScreen(byte screenCode, byte button) {
  switch (screenCode) {
    case SCR_CONFIG_MODEM_TO_MEM: {
        break;
      }
    case SCR_CONFIG_MODEM_TO_SCREEN: {
        updateOffset(button, 9);
        showSrcModemToScreen();
        break;
      }
    case SCR_CONFIG_MEM_TO_MODEM: {
        break;
      }
    case SCR_CONFIG_MEM_TO_SCREEN: {
        break;
      }
  }
}

void ScreenHandler::updateOffset(byte button, byte naxValue) {
  switch (button) {
    case BUTTON_UP: {
        if (displayOffset > 0) {
          displayOffset--;
        }
        break;
      }
    case BUTTON_DOWN: {
        if (displayOffset < naxValue) {
          displayOffset++;
        }
      }
  }
}

void ScreenHandler::showSrcModemToScreen(void) {
  if (!isDataCached) {
    modem->atsAll(modemConfig);
    isDataCached = true;
  }
  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0, 0);
  display->setTextColor(BLACK);

//  if (displayOffset < 1) {
//    printLine("FORMAT=", long(modemConfig[0]));
//  }
  if (displayOffset < 1) {
    printLine("PORT_SPD=", long(modemConfig[0]));
  }
  if (displayOffset < 2) {
    printLine("AIR_SPD=", long(modemConfig[1]));
  }
  if (displayOffset < 3) {
    printLine("NETID=", long(modemConfig[2]));
  }
  if (displayOffset < 4) {
    printLine("TXPOWER=", long(modemConfig[3]));
  }
  if (displayOffset < 5) {
    printLine("ECC=", long(modemConfig[4]));
  }
  if (displayOffset < 6) {
    printLine("MAVLINK=", long(modemConfig[5]));
  }
  if (displayOffset < 7) {
    printLine("OPPRESEND=", long(modemConfig[6]));
  }
  if (displayOffset < 8) {
    printLine("MIN_FRQ=", long(modemConfig[7]) * 1000);
  }
  if (displayOffset < 9) {
    printLine("MAX_FRQ=", long(modemConfig[8]) * 1000);
  }
  if (displayOffset < 10) {
    printLine("NUM_CHNLS=", long(modemConfig[9]));
    printLine("DUTY_CYCLE=", long(modemConfig[10]));
    printLine("LBT_RSSI=", long(modemConfig[11]));
    printLine("MANCHESTER=", long(modemConfig[12]));
    printLine("RTSCTS=", long(modemConfig[13]));
    printLine("MAX_WINDOW=", long(modemConfig[14]));
  }
  display->display();
}

void ScreenHandler::printLine(String label, long value) {
  char row[14];
  label += String(value);

  int strLength = label.length() + 1;

  char strArray[strLength];
  label.toCharArray(strArray, strLength);

  for (int i = 0; i < 14; i++)  {
    if (i < strLength) {
      row[i] = strArray[i];
    } else {
      row[i] = 0x20;
    }
  }

  for (int i = 0; i < 14; i++) {
    display->print(row[i]);
  }
}

