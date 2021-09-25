#ifndef BATTERYMONITOR_H_
#define BATTERYMONITOR_H_

#include "DisplayController.h"

#define BATTERY_PIN 35

int batteryLevel=-1;

void checkAndShow() {
  // voltage at pin: 3.11V with full batteries, 2.74V with empty batteries (4095-3200)
  if (batteryLevel<0)
    batteryLevel=analogRead(BATTERY_PIN)-3200;
  if (batteryLevel<0) batteryLevel=0;
  clear(CRGB::Black);
  showNumber37(batteryLevel/9);
}

#endif /* BATTERYMONITOR_H_ */
