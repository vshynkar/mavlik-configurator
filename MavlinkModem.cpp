#include <stdlib.h>
#include "MavlinkModem.h"

void MavlinkModem::init() {
  Serial.begin(BOUND_RATE);
}

