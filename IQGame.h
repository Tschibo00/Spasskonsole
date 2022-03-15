#ifndef IQGAME_H_
#define IQGAME_H_

#include "Game.h"

class IQGame: public Game {
	private:
    uint8_t countdown;
    uint8_t iq;
		void initLevel();
    
	public:
		IQGame();
		void play() override;
    bool needsPlayerSelection() override{
      return false;
    }
};

#endif
