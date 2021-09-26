#include "SoundController.h"

#include "zombie.h"
#include "gameover.h"

#define OUTPIN 25
#define PWM_CHANNEL 1

XT_Wav_Class Zombie(zombie2_wav);
XT_Wav_Class GameOver(gameover2_wav);
XT_DAC_Audio_Class DacAudio(OUTPIN,0);

void initSoundController(){
}

void processSound(){
  DacAudio.FillBuffer();
}

void playSound(float speed){
  Zombie.Speed=speed;
  DacAudio.Play(&Zombie);
}
