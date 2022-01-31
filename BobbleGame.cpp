#include "BobbleGame.h"

BobbleGame::BobbleGame(){
  level=0;
  initLevel();
}

void BobbleGame::play(){
  clear(CRGB::Black);

  if (targetLine<yPos)yPos--;
  if (targetLine>yPos)yPos++;

  drawScreen();

  switch(gameState){
    case BOB_STATE_MOVE:{
      move();
      Point hit=drawLineTest(4,7,4+angle,-40,bobbleColor(bobbles[0])/16);
      setScreen(hit.x,hit.y,bobbleColor(bobbles[0])/colDiv);
      colDiv^=32;
      drawBobble(4,7,bobbles[0]);
      break;}
    case BOB_STATE_FLY:{
      Point hit=drawLineTest(4,7,4+angle,-40,flying,bobbleColor(bobbles[0]),bobbleColor(bobbles[0])/16);
      if (hit.x>=0){
        Serial.println("hit 0");
        screen[hit.x+hit.y*8]=bobbles[0];
        adjustLastLine();
        flying=-1;
        if (getConnected(hit.x,hit.y,bobbles[0])>=2){// 3 connected, but the one that's shot isn't counted yet
        Serial.println("connected>2");
          initGoing();
          removeX=hit.x;
          removeY=hit.y;
          removeColor=bobbles[0];
          gameState=BOB_STATE_REMOVE;
        }else{
        Serial.println("state_move");
          gameState=BOB_STATE_MOVE;
          bobbles[0]=bobbles[1];
          initBobble(1,true);
        }
        Serial.println("adjust last line");
      }else{
        Serial.println("flying++");
        flying++;
        if (flying>50){
          flying=-1;
          gameState=BOB_STATE_MOVE;
        }
      }
      break;}
    case BOB_STATE_REMOVE:
        Serial.println("remove");
      if (checkAndRemoveConnected()){
        Serial.println("remove unconnected");
        removeUnconnected();
        gameState=BOB_STATE_MOVE;
        bobbles[0]=bobbles[1];
        initBobble(1,true);
        initBobble(0,false);
      }
      break;
  }
}

void BobbleGame::drawBobble(uint8_t x,uint8_t y,uint8_t bobble){
  set(x,y,bobbleColor(bobble));
}

void BobbleGame::drawScreen(){
  for (i=0;i<6*8;i++)
    drawBobble(i%8,i/8,screen[i+yPos*8]);
}

// returns true if no more bobbles are removed
bool BobbleGame::checkAndRemoveConnected(){
  going[removeX+removeY*8]=true;
  screen[removeX+removeY*8]=0;
  bool removed=false;
  for (i=0;i<8*40;i++)
    if (going[i])
      removed|=(getConnectedAndRemove(i%8,i/8,removeColor)>0);
  return !removed;
}

void BobbleGame::initGoing(){
  for (i=0;i<8*40;i++) going[i]=false;
}

void BobbleGame::removeUnconnected(){
  initGoing();

  for(x=0;x<8;x++)if(getScreen(x,0))going[x]=true;
  for(i=0;i<40;i++){
    for(y=0;y<40;y++)
      for(x=0;x<8;x++){
        if (getScreen(x,y)!=0){
          for(dy=-1;dy<=1;dy++)
            for(dx=-1;dx<=1;dx++)
              if (getGoing(x+dx,y+dy)!=0)
                going[x+y*8]=true;
        }
      }
  }

  bobblesRemoved=0;
  for (i=0;i<8*40;i++)
    if (!going[i]){
      screen[i]=0;
      bobblesRemoved++;
    }
  if (bobblesRemoved==8*40){
    Serial.println("CLEARED");
    level++;
    initLevel();
    showLevel();
  }

  adjustLastLine();
}

void BobbleGame::adjustLastLine(){
  lastLine=getLastLine()-5;
  targetLine=lastLine>=0?lastLine:0;
}

void BobbleGame::getAnyConnectedBobbles(int8_t x, int16_t y, uint8_t recursion){
  if (recursion>100)return;

  going[x+y*8]=true;

  for (dy=-1;dy<=1;dy++)
    for (dx=-1;dx<=1;dx++)
      if ((dx!=0)||(dy!=0))
        if ((x+dx>=0)&&(x+dx<8)&&(y+dy>=0)&&(y+dy<height))
          if ((!going[x+dx+(y+dy)*8])&&getAnyConnectedBobble(x+dx,y+dy)){
            getAnyConnectedBobbles(x+dx,y+dy,recursion+1);
            going[x+dx+(y+dy)*8]=true;
          }
}

bool BobbleGame::getAnyConnectedBobble(int8_t x, int16_t y){
  return getHit(x,y);
}

uint8_t BobbleGame::getConnectedAndRemove(int8_t x, int16_t y, uint8_t bobble){
  // TODO break on special bobbles
  uint8_t sum=0;

  for (dy=-1;dy<=1;dy++)
    for (dx=-1;dx<=1;dx++)
      if ((dx!=0)||(dy!=0))
        if ((x+dx>=0)&&(x+dx<8)&&(y+dy>=0)&&(y+dy<height))
          if (!going[x+dx+(y+dy)*8])
            if (getConnectedBobble(x+dx,y+dy,bobble)){
              going[x+dx+(y+dy)*8]=true;
              screen[x+dx+(y+dy)*8]=0;
              sum++;
            }
  return sum;
}

uint16_t BobbleGame::getConnected(int8_t x,int16_t y,uint8_t bobble){
  initGoing();
  uint16_t result=getConnectedBobbles(x,y,bobble,0);

Serial.print("connected ");
Serial.println(result);
  
  return result;
}

uint16_t BobbleGame::getConnectedBobbles(int8_t x, int16_t y, uint8_t bobble,uint8_t recursion){
uint16_t sum=0;
uint16_t oldSum;

int oldHeight=height;
height=40;

//TODO UNCOMMENT  do{
oldSum=sum;
going[x+y*8]=true;
for (i=0;i<40;i++)
for(y0=0;y0<height;y0++)
for(x0=0;x0<8;x0++)
if (going[x0+y0*8])

  for (dy=-1;dy<=1;dy++)
    for (dx=-1;dx<=1;dx++)
      if ((dx!=0)||(dy!=0))
        if ((x0+dx>=0)&&(x0+dx<8)&&(y0+dy>=0)&&(y0+dy<height))
          if ((!going[x0+dx+(y0+dy)*8])&&getConnectedBobble(x0+dx,y0+dy,bobble)){
//            Serial.print(x0+dx);Serial.print(" ");Serial.println(y0+dy);
            sum++;
            going[x0+dx+(y0+dy)*8]=true;
          }
//TODO UNCOMMENT  }while(sum>oldSum);
//  Serial.print("sum ");Serial.println(sum);

  height=oldHeight;
  
  return sum;
}

bool BobbleGame::getConnectedBobble(int8_t x, int16_t y, uint8_t bobble){
  if ((x<0)||(x>7)||(y<0)||(y>=height))return false;
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
  height=rand()%29+10;  //height may not be larger than max height -2

//  height=6;//TODO REVERT
  mask=0;// TODO REVERT

  for(i=0;i<8*40;i++)screen[i]=0;

  uint8_t c,m;
  for (i=0;i<height*8;i++){
    c=rand()%colorMod;
    m=rand()&mask;
    screen[i]=c|m;
  }

/*  //TODO REVERT
  for(i=0;i<height;i++){
    screen[i*8]=0;
    screen[i*8+1]=0;
    screen[i*8+2]=0;
    screen[i*8+3]=0;
  }
  */

/*
for (y=0;y<6;y++)
for(x=0;x<8;x++)
screen[y*8+x]=(y+x)%colorMod;
height=6;
*/

removeUnconnected();
  
  initBobble(0,true);
  initBobble(1,true);

  targetLine=height-6;
  yPos=0;
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
  gameState=BOB_STATE_FLY;
  flying=1;
}

void BobbleGame::initBobble(uint8_t i,bool randomize){
  if(randomize){
    do{
      bobbles[i]=rand()%colorMod;
    }while((bobbles[i]==0)||(!checkIfColorAvailable(bobbles[i])));
  }else{
    while((bobbles[i]==0)||(!checkIfColorAvailable(bobbles[i]))){
      bobbles[i]=rand()%colorMod;
    }
  }
}

bool BobbleGame::checkIfColorAvailable(uint8_t bobbleColor){
  for(i=0;i<8*40;i++)
    if(screen[i]==bobbleColor)return true;
  return false;
}

void BobbleGame::move(){
  switch (getNumberClick()) {
    case KEY_1:level--;initLevel();break;//TODO temp
    case KEY_2:level++;initLevel();break;//TODO temp
    case KEY_UP:rotateBobble(true);break;
    case KEY_DOWN:rotateBobble(false);break;
    case KEY_OK:shoot();break;

    case KEY_5: if(yPos>0)yPos--;break;
    case KEY_8: if(yPos<33)yPos++;break;
  }

  if (getKeyStatus(KEY_LEFT)&&(angle>-100))angle-=2;
  if (getKeyStatus(KEY_RIGHT)&&(angle<100))angle+=2;
}

Point BobbleGame::drawLineTest(int x0,int y0,int x1,int y1, CRGB color){
  uint8_t steps;
  if (abs(y1-y0)>abs(x1-x0))
    steps=abs(y1-y0);
  else
    steps=abs(x1-x0);

  if (steps==0)
    return drawLineTest(x0,y0+yPos,0,0,0,color);
  else
    return drawLineTest(x0,y0+yPos,(x1-x0)*256/steps,(y1-y0)*256/steps,steps,color);
}

Point BobbleGame::drawLineTest(int x0,int y0,int dx,int dy, uint8_t steps, CRGB color){
  Point hit;
  hit.x=-1;
  hit.y=-1;

  x0=x0*256+128;
  y0=y0*256+128;
  for (i = 0; i <= steps; i++) {
    if (getHit(x0>>8,y0>>8))return hit;
    setScreen(x0>>8, y0>>8, color);
    hit.x=x0>>8;
    hit.y=y0>>8;
    x0+=dx;
    y0+=dy;
    if ((x0<256)||(x0>1792))dx=-dx;//bound of the edges
  }
}

Point BobbleGame::drawLineTest(Point p0,Point p1,uint8_t steps,CRGB color){
  return drawLineTest(p0.x,p0.y,p1.x,p1.y,steps,color);
}

Point BobbleGame::drawLineTest(int x0,int y0,int x1,int y1,uint8_t index,CRGB bobble,CRGB color){
  uint8_t steps;
  if (abs(y1-y0)>abs(x1-x0))
    steps=abs(y1-y0);
  else
    steps=abs(x1-x0);

  if (steps==0)
    return drawLineTest(x0,y0+yPos,0,0,0,index,bobble,color);
  else
    return drawLineTest(x0,y0+yPos,(x1-x0)*256/steps,(y1-y0)*256/steps,steps,index,bobble,color);
}

Point BobbleGame::drawLineTest(int x,int y,int dx,int dy, uint8_t steps, uint8_t index, CRGB bobble,CRGB color){
  Point hit;
  hit.x=-1;
  hit.y=-1;
  
  x=x*256+128;
  y=y*256+128;
  for (uint8_t i = 0; i <= steps; i++) {
    if (i>=index){
      if (getHit(x>>8,y>>8))return hit;
      setScreen(x>>8, y>>8, bobble);
    }
    hit.x=x>>8;
    hit.y=y>>8;
    x+=dx;
    y+=dy;
    if ((x<256)||(x>1792))dx=-dx;//bounce of the edges

    if (y<0){
    hit.x=x>>8;
    hit.y=0;
    return hit;
    }

    Serial.print(x);Serial.print("  ");Serial.println(y);
  }
  hit.x=hit.y=-1;
  return hit;
}

bool BobbleGame::getHit(int x,int y){
  return getScreen(x,y)!=0;
}

uint8_t BobbleGame::getLastLine(){
  for (y=39;y>=0;y--)
    for (x=0;x<8;x++)
      if (screen[y*8+x]!=0) return y;
}

uint8_t BobbleGame::getScreen(int x,int y){
  if ((x<0)||(x>7)||(y<0)||(y>=39))return 0;
  return screen[x+y*8];
}

uint8_t BobbleGame::getGoing(int x,int y){
  if ((x<0)||(x>7)||(y<0)||(y>=39))return 0;
  return going[x+y*8];
}
