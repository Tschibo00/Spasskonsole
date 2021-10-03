#include "GameController.h"
#include "BatteryMonitor.h"

#define GAME_COUNT 1
#define SKIP_LOGO

Game *runningGame = NULL;
char state = GAME_BATTERY;
int currentGame = -1;
char selectedPlayer = 0;
bool resetPlayer = false;
int scrollPos=0;

/*
 *       set(xB,yB,CRGB::Red);
      set(xB+1,yB,CRGB::Grey);
      set(xB+2,yB,CRGB::Red);
      set(xB,yB+1,CRGB::Blue);
      set(xB+1,yB+1,CRGB::Blue);
      set(xB+2,yB+1,CRGB::Blue);
      set(xB,yB+2,CRGB::White);
      set(xB+2,yB+2,CRGB::White);

    // player
    bool hitBoss=false;
    if (safety%2==0){
      hitBoss|=setTest(x,y,CRGB::White);
      hitBoss|=setTest(x,y+1,CRGB::Blue);

 */
static const uint8_t icons[1][64] = {
  {0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,    0,0,255,0,0,0,0,0,    0,0,3,0,0,0,0,0,    0,0,0,0,224,146,224,0,   0,0,0,0,3,3,3,0,    0,0,0,0,255,0,255,0,  0,0,0,0,0,0,0,0}
//  { 3,7,10,14,17,21,24,28,  35,39,42,46,49,53,56,60,  66,70,73,77,80,84,88,92,  98,102,105,109,112,116,120,124,  129,133,136,140,144,148,152,156,  161,165,168,172,176,180,184,188,  192,196,200,204,208,212,216,220,  224,228,232,236,240,244,248,252 }		// BossGame
};

void initGameController(){
}

void initGame(int game){
	switch (game) {
		case 0:
			runningGame = new BossGame();
			break;
	}
	if (runningGame->needsPlayerSelection())
		state = GAME_PLAYER_SELECTION;
	else
		state = GAME_RUNNING;
}

void play(){
	char select;
	switch (state) {
    case GAME_BATTERY:
      checkAndShow();
      scrollPos++;
      if (scrollPos>30){
        scrollPos=-10;
        state=GAME_STARTUP;
      }
      break;
		case GAME_STARTUP:
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

			if (currentGame >= 0)
				copy(icons[currentGame]);
			else{
        #ifdef SKIP_LOGO
        scrollPos=207;
        #endif
        if (getKeyStatus(KEY_OK))
          scrollPos=207;
        showScroller("Spasskonsole  ", scrollPos/2, true, true, CRGB::Black);
        scrollPos++;
        if (scrollPos>206) currentGame=0;
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
