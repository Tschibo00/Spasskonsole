#ifndef IQGAME_H_
#define IQGAME_H_

#include "Game.h"

class IQGame: public Game {
	private:

		void initLevel();
		void move();
    
	public:
		IQGame();
		void play() override;
    bool needsPlayerSelection() override{
      return false;
    }
};

#endif
