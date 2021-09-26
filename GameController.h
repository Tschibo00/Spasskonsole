#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "Game.h"
#include "BossGame.h"
#include <math.h>
//#include "avr/pgmspace.h"

//#include "DisplayController.h"
//#include "SoundController.h"

#define GAME_BATTERY 0
#define GAME_STARTUP 1
#define GAME_PLAYER_SELECTION 2
#define GAME_RUNNING 3

void initGameController();
void play();
void showPlayerName(uint8_t player);

#endif
