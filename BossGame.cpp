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

  // player
  set(x,y,CRGB::White);
  set(x,y+1,CRGB::Blue);

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



//  for (uint8_t i=0;i<64;i++)
  //  set(i%8,i/8,getFullColor(screen[i]));

  
}

void BossGame::initLevel(){
  x=y=4;
  initBoss();
}

void BossGame::move(){
 
	switch (getNumberClick()) {
    case 15:
      if (y>0) y--;
      break;
    case 17:
      if (y<6) y++;
      break;
    case 18:
      if (x>0) x--;
      break;
    case 19:
      if (x<7) x++;
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
  isBoss=random(7)==0;
  isLeaving=false;
  if (isBoss)
    playSound(0.9f);
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
