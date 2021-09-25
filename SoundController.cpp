#include "SoundController.h"

#include "SoundData.h"

#define OUTPIN 25
#define PWM_CHANNEL 1

XT_Wav_Class ForceWithYou(Force);
XT_DAC_Audio_Class DacAudio(OUTPIN,0);

void initSoundController(){
}

void processSound(){
  DacAudio.FillBuffer();
}

void playSound(float speed){
  ForceWithYou.Speed=speed;
  DacAudio.Play(&ForceWithYou);
}
