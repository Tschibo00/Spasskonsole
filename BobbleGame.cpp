#include "BobbleGame.h"

BobbleGame::BobbleGame(){
  level=0;
  initLevel();
}

void BobbleGame::play(){
  clear(CRGB::Black);

  move();

  for (uint16_t i=yPos*8;i<height*8;i++)
    drawBobble(i%8,i/8-yPos,screen[i]);
Serial.println(flying);
  if (flying<0){
    Point hit=drawLineTest(4,7,4+angle,-20,bobbleColor(bobbles[0])/16);
    set(hit.x,hit.y,bobbleColor(bobbles[0])/colDiv);
    colDiv^=32;
  }else{
    if (drawLineTest(4,7,4+angle,-20,flying,bobbleColor(bobbles[0]),bobbleColor(bobbles[0])/16)){
      // set bobble fixed to screen
      flying=-1;
    }else{
      flying++;
    }
  }
  drawBobble(4,7,bobbles[0]);
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
  flying=0;
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

  if (getKeyStatus(KEY_LEFT)&&(angle>-40))angle--;
  if (getKeyStatus(KEY_RIGHT)&&(angle<40))angle++;
}
