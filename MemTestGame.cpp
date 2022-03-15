#include "MemTestGame.h"

MemTestGame::MemTestGame(){
	initLevel();
}

void MemTestGame::play(){
	clear(CRGB::Black);
}

void MemTestGame::initLevel(){
}

void MemTestGame::move(){
 
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
