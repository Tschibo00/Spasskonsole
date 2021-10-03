#ifndef BOBBLEGAME_H_
#define BOBBLEGAME_H_

#include "Game.h"

class BobbleGame: public Game {
  private:
    void initLevel();
    void move();


  public:
    BobbleGame();
    void play() override;
    bool needsPlayerSelection() override{
      return true;
    }
};

#endif
