#ifndef SOUND_CONTROLLER
#define SOUND_CONTROLLER

#include <Arduino.h>
#include "XT_DAC_Audio.h"

void initSoundController();
void processSound();
void playSound(float speed);
void playGameOver();
void playLost();

#endif
