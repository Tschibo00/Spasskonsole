#ifndef MEMTESTGAME_H_
#define MEMTESTGAME_H_

#include "Game.h"

class MemTestGame: public Game {
	private:
		void initLevel();
		void move();

	public:
		MemTestGame();
		void play() override;
    bool needsPlayerSelection() override{
      return false;
    }
};

#endif
