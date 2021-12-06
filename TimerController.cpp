#include "TimerController.h"
#include "KeyboardController.h"
#include "GameController.h"

hw_timer_t *timerGameloop=NULL;
hw_timer_t *timerKeyboard=NULL;

bool timerGameRunning;
bool timerKeyboardRunning;

void IRAM_ATTR onKeyboard() {
  scanKeyboard();
}

void IRAM_ATTR onGameloop() {
  Serial.println("timer begin");
  play();
  Serial.println("timer end");
}

void initTimers(){ 
  timerGameRunning=false;
  timerKeyboardRunning=false;
  
  timerGameloop=timerBegin(1, 80, true);                    // pre-scaler of 80, resulting in 1Mhz
  timerAttachInterrupt(timerGameloop, &onGameloop, true);
  timerAlarmWrite(timerGameloop, 40000, true);              // called 25 times/s
  timerStart(timerGameloop);

  timerKeyboard=timerBegin(2, 80, true);                    // pre-scaler of 80, resulting in 1Mhz
  timerAttachInterrupt(timerKeyboard, &onKeyboard, true);
  timerAlarmWrite(timerKeyboard, 8000, true);              // called 125 times/s
  timerStart(timerKeyboard);
  timerAlarmEnable(timerKeyboard);
}

void startTimers(){
  timerAlarmEnable(timerGameloop);
  timerAlarmEnable(timerKeyboard);
}

void pauseTimers(){
/*  Serial.println("attempting to pause timers");
  while(timerGameRunning||timerKeyboardRunning){
    Serial.print(timerGameRunning);Serial.print(" ");Serial.println(timerKeyboardRunning);
    if (!timerGameRunning) timerAlarmDisable(timerGameloop);
    if (!timerKeyboardRunning) timerAlarmDisable(timerKeyboard);
    delay(10);
  }
  Serial.println("timers are now paused");*/
}

void setTimerGameRunning(bool running){
  timerGameRunning=running;
}

void setTimerKeyboardRunning(bool running){
  timerKeyboardRunning=running;
}
  
