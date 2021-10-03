#include "BossGame.h"

BossGame::BossGame(){
	initLevel();
}

void BossGame::play(){
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

  if (showingScore>=0){
    setNumber(survived);
    showScroller(score,(showingScore-15)/2,true,CRGB::White);
    showingScore=(showingScore+1)%96;
  }else{
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
    bool hitBoss=false;
    if (safety%2==0){
      hitBoss|=setTest(x,y,CRGB::White);
      hitBoss|=setTest(x,y+1,CRGB::Blue);
    }
    if (safety>0){
      safety--;
      hitBoss=false;
    }
    if (hitBoss){
      if (survived==0){
        initLevel();
        playGameOver();
      }else{
        safety=25;
        survived=0;
        playLost();
      }
    }
  }
}

void BossGame::initLevel(){
  x=y=4;
  safety=0;
  bossSpeed=7;
  bossCounter=7;
  showingScore=-1;
  initBoss();
  survived=0;
}

void BossGame::move(){
 
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
  survived++;
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
