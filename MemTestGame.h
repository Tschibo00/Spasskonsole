#ifndef MEMTESTGAME_H_
#define MEMTESTGAME_H_

#include "Game.h"
#include "MemController.h"

class MemTestGame: public Game {
	public:
		MemTestGame();
		void play() override;
    bool needsPlayerSelection() override{
      return false;
    }
};

#endif
