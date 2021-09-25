#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "Game.h"
#include "BossGame.h"
#include <math.h>
//#include "avr/pgmspace.h"

//#include "DisplayController.h"
//#include "SoundController.h"

#define GAME_STARTUP 0
#define GAME_PLAYER_SELECTION 1
#define GAME_RUNNING 2

void initGameController();
void selectGame(int game);
void play();

#endif
