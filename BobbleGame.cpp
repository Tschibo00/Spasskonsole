#include "BobbleGame.h"

BobbleGame::BobbleGame(){
  level=0;
  initLevel();
}

void BobbleGame::play(){
  clear(CRGB::Black);

  move();

  drawScreen();
  if (flying<0){
    Point hit=drawLineTest(4,7,4+angle,-20,bobbleColor(bobbles[0])/16);
    set(hit.x,hit.y,bobbleColor(bobbles[0])/colDiv);

    colDiv^=32;
  }else{
    Point hit=drawLineTest(4,7,4+angle,-20,flying,bobbleColor(bobbles[0]),bobbleColor(bobbles[0])/16);
    if (hit.x>0){
      screen[hit.x+(hit.y+height-6)*8]=bobbles[0];
      flying=-1;
      bobbles[0]=bobbles[1];
      initBobble(1);
    }else{
      flying++;
    }
  }
  drawBobble(4,7,bobbles[0]);
}

void BobbleGame::drawBobble(uint8_t x,uint8_t y,uint8_t bobble){
  set(x,y,bobbleColor(bobble));
}

void BobbleGame::drawScreen(){
  for (uint16_t i=0;i<8*6;i++)
    drawBobble(i%8,i/8,screen[i+yPos*8]);
}

uint16_t BobbleGame::getConnected(int8_t x,int16_t y,uint8_t bobble){
  for (uint16_t i=0;i<8*40;i++) going[i]=false;
  return getConnectedBobbles(x,y,bobble,0);
}

uint16_t BobbleGame::getConnectedBobbles(int8_t x, int16_t y, uint8_t bobble,uint8_t recursion){
  // TODO break on special bobbles
  uint16_t sum=0;
  if (recursion>100)return 0;

  going[x+y*8]=true;

  for (int16_t dy=-1;dy<=1;dy++)
    for (int8_t dx=-1;dx<=1;dx++)
      if ((dx!=0)||(dy!=0))
        if ((x+dx>=0)&&(x+dx<8)&&(y+dy>=0)&&(y+dy<height))
          if ((!going[x+dx+(y+dy)*8])&&getConnectedBobble(x+dx,y+dy,bobble,recursion)){
            sum++;
            sum+=getConnectedBobbles(x+dx,y+dy,bobble,recursion+1);
            going[x+dx+(y+dy)*8]=true;
          }
  return sum;
}

bool BobbleGame::getConnectedBobble(int8_t x, int16_t y, uint8_t bobble,uint8_t recursion){
  return screen[x+y*8]==bobble;
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

  mask=0;

  uint8_t c,m;
  for (uint16_t i=0;i<height*8;i++){
    c=rand()%colorMod;
    m=rand()&mask;
    screen[i]=c|m;
  }

  //TODO REVERT
  for(uint8_t i=0;i<height;i++){
    screen[i*8]=CRGB::Black;
    screen[i*8+1]=CRGB::Black;
    screen[i*8+2]=CRGB::Black;
    screen[i*8+3]=CRGB::Black;
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
  flying=1;
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

    case KEY_5: yPos--;break;
    case KEY_8: yPos++;break;
  }

  if (getKeyStatus(KEY_LEFT)&&(angle>-40))angle--;
  if (getKeyStatus(KEY_RIGHT)&&(angle<40))angle++;
}
