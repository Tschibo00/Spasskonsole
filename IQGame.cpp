#include "IQGame.h"

IQGame::IQGame(){
	initLevel();
}

void IQGame::play(){
	clear(CRGB::Black);
}

void IQGame::initLevel(){
}

void IQGame::move(){
 
	switch (getNumberClick()) {
    case KEY_UP:
      break;
    case KEY_DOWN:
      break;
    case KEY_LEFT:
      break;
    case KEY_RIGHT:
      break;
	}
}
