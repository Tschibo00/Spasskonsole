#include "IQGame.h"

IQGame::IQGame(){
	initLevel();
}

void IQGame::play(){
  if (getKeyClick(KEY_1)){
    if (showingScore<0){
      if (survived<10) showingScore=64;
      if (survived>=10) showingScore=48;
      if (survived>=100) showingScore=32;
      if (survived>=1000) showingScore=16;
      if (survived>=10000) showingScore=0;
    }else
      showingScore=-1;
  }
	clear(CRGB::Black);
}

void IQGame::initLevel(){
}

void IQGame::move(){
 
	switch (getNumberClick()) {
    case KEY_UP:
      y--;
      if (y<-1) y=7;
      break;
    case KEY_DOWN:
      y++;
      if (y>7) y=-1;
      break;
    case KEY_LEFT:
      x--;
      if (x<0) x=7;
      break;
    case KEY_RIGHT:
      x++;
      if (x>7) x=0;
      break;
	}
}
