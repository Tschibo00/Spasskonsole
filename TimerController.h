#ifndef TIMERCONTROLLER_H_
#define TIMERCONTROLLER_H_

#include <Arduino.h>

void initTimers();
void pauseTimers();
void startTimers();
void setTimerGameRunning(bool running);
void setTimerKeyboardRunning(bool running);

#endif
