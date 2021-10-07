#include "BobbleGame.h"

BobbleGame::BobbleGame(){
  level=0;
  initLevel();
}

void BobbleGame::play(){
  clear(CRGB::Black);

/*  move();

  for (uint16_t i=yPos*8;i<height*8;i++)
    drawBobble(i%8,i/8-yPos,screen[i]);

  drawBobble(4,7,bobbles[0]);
//  drawLine(4,7,4+angle,-20,bobbles[0]);*/



  switch(getNumberClick()){
    case KEY_2:y0--;break;
    case KEY_4:x0--;break;
    case KEY_6:x0++;break;
    case KEY_8:y0++;break;
    case KEY_UP:y1--;break;
    case KEY_LEFT:x1--;break;
    case KEY_RIGHT:x1++;break;
    case KEY_DOWN:y1++;break;
  }

  drawLine(x0,y0,x1,y1,CRGB::White);


}

void BobbleGame::drawBobble(uint8_t x,uint8_t y,uint8_t bobble){
  set(x,y,bobbleColor(bobble));
}

CRGB BobbleGame::bobbleColor(uint8_t bobble){
  switch(bobble&7){ //TODO &7 only temporary to reduce complexity
    case 1:return CRGB::Red;break;
    case 2:return CRGB::Blue;break;
    case 3:return CRGB::Yellow;break;
    case 4:return CRGB::Green;break;
    case 5:return CRGB::Purple;break;
    default:return CRGB::Black;break;
  }
}

void BobbleGame::initLevel(){
  srand(level);
  colorMod=rand()%5+2;
  uint8_t mask=rand()&248;
  height=rand()%30+10;

  uint8_t c,m;
  for (uint16_t i=0;i<height*8;i++){
    c=rand()%colorMod;
    m=rand()&mask;
    screen[i]=c|m;
  }

  initBobble(0);
  initBobble(1);

  yPos=height-6;
  angle=0;
}

void BobbleGame::rotateBobble(bool up){
  uint8_t temp;
  if(up){
    temp=bobbles[0];
    bobbles[0]=bobbles[1];
    if(numberBobbles>2){
      bobbles[1]=bobbles[2];
      bobbles[2]=temp;
    }else{
      bobbles[1]=temp;
    }
  }else{
    if(numberBobbles>2){
      temp=bobbles[2];
      bobbles[2]=bobbles[1];
      bobbles[1]=bobbles[0];
      bobbles[0]=temp;
    }else{
      temp=bobbles[1];
      bobbles[1]=bobbles[0];
      bobbles[0]=temp;
    }
  }
}

void BobbleGame::shoot(){
  bobbles[0]=bobbles[1];
  initBobble(1);
}

void BobbleGame::initBobble(uint8_t i){
  do{
    bobbles[i]=rand()%colorMod;
  }while(bobbles[i]==0);
}

void BobbleGame::move(){
  switch (getNumberClick()) {
    case KEY_1:level--;initLevel();break;//TODO temp
    case KEY_2:level++;initLevel();break;//TODO temp
    case KEY_UP:rotateBobble(true);break;
    case KEY_DOWN:rotateBobble(false);break;
    case KEY_OK:shoot();break;
  }

  if (getKeyStatus(KEY_LEFT))angle--;
  if (getKeyStatus(KEY_RIGHT))angle++;
}
