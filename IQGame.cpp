#include "IQGame.h"

IQGame::IQGame(){
	initLevel();
}

void IQGame::play(){
  if (countdown>0){
    iq=rand()%30+90;
    countdown--;
  }

	clear(CRGB::Black);
  showNumber37(iq);

  if (anyKeyClick(0,23))
    initLevel();
}

void IQGame::initLevel(){
  countdown=30;
}
