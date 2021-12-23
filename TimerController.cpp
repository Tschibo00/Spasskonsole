#include "TimerController.h"
#include "KeyboardController.h"
#include "GameController.h"

hw_timer_t *timerGameloop=NULL;
hw_timer_t *timerKeyboard=NULL;

void IRAM_ATTR onKeyboard() {
  scanKeyboard();
}

void IRAM_ATTR onGameloop() {
  play();
}

void initTimers(){ 
  timerGameloop=timerBegin(1, 80, true);                    // pre-scaler of 80, resulting in 1Mhz
  timerAttachInterrupt(timerGameloop, &onGameloop, true);
  timerAlarmWrite(timerGameloop, 40000, true);              // called 25 times/s
  timerStart(timerGameloop);

  timerKeyboard=timerBegin(2, 80, true);                    // pre-scaler of 80, resulting in 1Mhz
  timerAttachInterrupt(timerKeyboard, &onKeyboard, true);
  timerAlarmWrite(timerKeyboard, 8000, true);               // called 125 times/s
  timerStart(timerKeyboard);

  timerAlarmEnable(timerGameloop);
  timerAlarmEnable(timerKeyboard);
}
