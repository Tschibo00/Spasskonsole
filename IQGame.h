#ifndef IQGAME_H_
#define IQGAME_H_

#include "Game.h"

class IQGame: public Game {
	private:

		void initLevel();
		void move();

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
		IQGame();
		void play() override;
    bool needsPlayerSelection() override{
      return false;
    }
};

#endif
