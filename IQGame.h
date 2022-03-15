#ifndef BOSSGAME_H_
#define BOSSGAME_H_

#include "Game.h"

class BossGame: public Game {
	private:
    int8_t x,y;
    int8_t xB,yB;
    int bossEnd;
    int bossNextStep;
    int bossSpeed;
    int8_t bossCounter;
    bool isBoss;
    bool isLeaving;
    uint16_t survived;
    int8_t safety;
    int16_t showingScore;
    char score[6];
    uint8_t screen[64];

		void initLevel();
		void move();
    void initBoss();
    void moveBoss();

    bool setChar(uint8_t i,uint8_t n, bool showZero){
      if (i>4)return false;
      if ((!showZero)&&(n==0))
        score[i]=32;
      else
        score[i]=48+n;
      return n!=0;
    }
    void setNumber(uint16_t n){
      bool zero=false;
      zero|=setChar(0,(n/10000)%10,zero);
      zero|=setChar(1,(n/1000)%10,zero);
      zero|=setChar(2,(n/100)%10,zero);
      zero|=setChar(3,(n/10)%10,zero);
      zero|=setChar(4,n%10,true);
      score[5]=32;
    }
    
	public:
		BossGame();
		void play() override;
    bool needsPlayerSelection() override{
      return false;
    }
};

#endif
