#include "GameController.h"
#include "BatteryMonitor.h"

#define GAME_COUNT 2
//#define SKIP_LOGO

Game *runningGame = NULL;
char state = GAME_BATTERY;
int currentGame = -1;
char selectedPlayer = 0;
bool resetPlayer = false;
int scrollPos=0;

static const uint8_t icons[GAME_COUNT][64] = {
  {0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,    0,0,255,0,0,0,0,0,    0,0,3,0,0,0,0,0,    0,0,0,0,224,146,224,0,   0,0,0,0,3,3,3,0,    0,0,0,0,255,0,255,0,  0,0,0,0,0,0,0,0},
  {3,3,252,224,224,252,3,252,   3,252,252,224,3,224,252,224,    252,252,0,0,3,0,252,224,    64,224,0,224,3,252,252,0,    0,64,252,252,3,224,0,224,  0,0,64,0,252,0,224,0,    0,0,0,64,0,0,0,0,    146,0,0,0,224,0,0,0}
};

void initGameController(){
}

void initGame(int game){
	switch (game) {
		case 0:
			runningGame = new BossGame();
			break;
    case 1:
      runningGame = new BobbleGame();
      break;
	}
	if (runningGame->needsPlayerSelection())
		state = GAME_PLAYER_SELECTION;
	else
		state = GAME_RUNNING;
}

void play(){
  setTimerGameRunning(true);
  
	char select;
	switch (state) {
    case GAME_BATTERY:
      checkAndShow();
      scrollPos++;
      if ((scrollPos>30)||getKeyClick(KEY_OK)){
        scrollPos=-10;
        state=GAME_STARTUP;
      }
      break;
		case GAME_STARTUP:

			if (currentGame >= 0){
        select = getNumberClick();
        switch(select){
          case KEY_LEFT:
            currentGame--;
            if (currentGame<0) currentGame=GAME_COUNT-1;
            break;
          case KEY_RIGHT:
            currentGame++;
            if (currentGame>=GAME_COUNT) currentGame=0;
            break;
          case KEY_OK:
            initGame(currentGame);
            break;
        }
				copy(icons[currentGame]);
			}else{
        #ifdef SKIP_LOGO
        scrollPos=200;
        #endif
        if (getKeyClick(KEY_OK))
          scrollPos=200;
        showScroller("Spasskonsole  ", scrollPos/2, true, true, CRGB::Black);
        scrollPos++;
        if (scrollPos>=200) currentGame=0;
			}
			break;
		case GAME_PLAYER_SELECTION:
      select=getNumberClick();
      switch(select){
        case KEY_LEFT:
          selectedPlayer--;
          if (selectedPlayer < 0) selectedPlayer = 3;
          scrollPos=-16;
          break;
        case KEY_RIGHT:
          selectedPlayer++;
          if (selectedPlayer >3) selectedPlayer = 0;
          scrollPos=-16;
          break;
        case KEY_OK:
          resetPlayer=false;  // TODO REMOVE
          runningGame->selectPlayer(selectedPlayer, resetPlayer);
          state = GAME_RUNNING;
          break;
      }
      showPlayerName(selectedPlayer);
			break;
		case GAME_RUNNING:
			runningGame->play();
			break;
	}

  setTimerGameRunning(false);
}

void showPlayerName(uint8_t player){
  scrollPos++;
  switch(player){
    case 0:
      showScroller("Peter ",scrollPos/2,true,EFFECT_FADE,CRGB::White,CRGB::Blue);
       if (scrollPos>84) scrollPos=-16;
      break;
    case 1:
      showScroller("Martin ",scrollPos/2,true,EFFECT_FADE,CRGB::Red,CRGB::Green);
      if (scrollPos>100) scrollPos=-16;
      break;
    case 2:
      showScroller("Simone ",scrollPos/2,true,EFFECT_FADE,CRGB(255,0,150),CRGB::Green);
      if (scrollPos>100) scrollPos=-16;
      break;
    case 3:
      showScroller("Hannes ",scrollPos/2,true,EFFECT_FADE,CRGB::Yellow,CRGB::Red);
      if (scrollPos>100) scrollPos=-16;
      break;
  }
}
