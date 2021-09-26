#include "BossGame.h"

uint8_t screen[64];

BossGame::BossGame(){
	initLevel();

  for (uint8_t y=0;y<8;y++)
    for (uint8_t x=0;x<8;x++)
      screen[y*8+x]=(y<<2)|(x<<5);
}

void BossGame::play(){
	clear(CRGB::Black);

	move();
	moveBoss();

  if (isBoss){
    set(xB,yB,CRGB::Red);
    set(xB+1,yB,CRGB::Grey);
    set(xB+2,yB,CRGB::Red);
    set(xB,yB+1,CRGB::Blue);
    set(xB+1,yB+1,CRGB::Blue);
    set(xB+2,yB+1,CRGB::Blue);
    set(xB,yB+2,CRGB::White);
    set(xB+2,yB+2,CRGB::White);
  }else{
    set(xB,yB,CRGB::Red);
    set(xB+1,yB,CRGB::Orange);
    set(xB,yB+1,CRGB::Green);
    set(xB+1,yB+1,CRGB::Purple);
  }

  // player
  set(x,y,CRGB::White);
  set(x,y+1,CRGB::Blue);
}

void BossGame::initLevel(){
  x=y=4;
  initBoss();
}

void BossGame::move(){
 
	switch (getNumberClick()) {
    case 15:
      y--;
      if (y<-1) y=7;
      break;
    case 17:
      y++;
      if (y>7) y=-1;
      break;
    case 18:
      x--;
      if (x<0) x=7;
      break;
    case 19:
      x++;
      if (x>7) x=0;
      break;
	}
}

void BossGame::initBoss(){
  bossNextStep=bossSpeed;
  bossEnd=100;
  do{
    xB=random(3)*7-3;
    yB=random(3)*7-3;
  }while((xB==4)&&(yB==4));   // don't allow to start on middle of screen
  bossCounter--;
  if (bossCounter<0){
    isBoss=true;
    bossCounter=7;
    bossSpeed--;
    if (bossSpeed<1) bossSpeed=1;
  }else
    isBoss=false;
  isLeaving=false;
  if (isBoss)
    playSound(1.5f);
}

void BossGame::moveBoss(){
  bossEnd--;
  bossNextStep--;
  if (bossNextStep>=0)
    return;

  bossNextStep=bossSpeed;
  if (bossEnd<0){
    isLeaving=true;
  }

  if (isLeaving){
    if ((xB<4)&&(yB<4))xB--;
    if ((xB<4)&&(yB>=4))yB++;
    if ((xB>=4)&&(yB>=4))xB++;
    if ((xB>=4)&&(yB<4))yB--;
    if ((xB<-2)||(xB>7)||(yB<-2)||(yB>7))
      initBoss();
  }else{
    int8_t dx=random(3)-1;
    int8_t dy=random(3)-1;
    if (xB<1)dx=1;
    if (xB>5)dx=-1;
    if (yB<1)dy=1;
    if (yB>5)dy=-1;
    xB+=dx;
    yB+=dy;
  }  
}
