#ifndef BOSSGAME_H_
#define BOSSGAME_H_

#include "Game.h"

class BossGame: public Game {
	private:
    int8_t x,y;
    int8_t xB,yB;
    int bossEnd;
    int bossNextStep;
    int bossSpeed=7;
    int8_t bossCounter=7;
    bool isBoss;
    bool isLeaving;

		void initLevel();
		void move();
    void initBoss();
    void moveBoss();

	public:
		BossGame();
		void play() override;
    bool needsPlayerSelection() override{
      return true;
    }
};

#endif
