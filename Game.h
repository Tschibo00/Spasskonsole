#ifndef GAME_H_
#define GAME_H_

#include <Arduino.h>

#include "DisplayController.h"
#include "KeyboardController.h"
#include "SoundController.h"
#include "TimerController.h"
//#include "MemController.h"

#define GAME_STATE_RUNNING 0
#define GAME_STATE_SHOW_LEVEL 1

static const char victoryScreen[20] = { 0, 0, 15, 15, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 };
static const char gameOverScreen[20] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 15, 15, 0, 0, 15, 15 };
/*static const char gameOverMusic[4] = { 10, 9, 8, 7 };
static const char victoryMusic[5] = { 13, PAUSE, 13, 13, 18 };
*/

static bool longRunningJob=false;

class Game {
/*	private:
		char scroller[9];
		void levelEnd(const char *screen, int level, char keyFirst, char keyLast){
			unsigned long start = millis();
			sprintf(scroller, "Level%d", level);
			while (!anyKeyClick(keyFirst, keyLast)) {
//				if (millis() - start < 1000L)
	//				copy(screen);
		//		else
					showScroller(scroller, ((millis() - start) / 200 + 19) % 32 - 4, true,CRGB::Green);
			}
		}

	protected:
		void victory(int level, char keyFirst, char keyLast){
//			music(victoryMusic, 5, 130, 600, -4);
			levelEnd(victoryScreen, level, keyFirst, keyLast);
		}

		void gameover(int level){
//			music(gameOverMusic, 4, 500, 500, -2);
			levelEnd(gameOverScreen, level, 0, 11);
		}
*/
  private:
    int scrollPos=0;
    char scroller[16];
    uint8_t state=GAME_STATE_RUNNING;

  protected:
    uint8_t level;

  void showLevel(){
    state=GAME_STATE_SHOW_LEVEL;
    scrollPos=0;
  }
  
  void showLevelNumber(){
//    memset(scroller,32,16);
    int l=sprintf(scroller, "Level %d", level);
    scroller[l]=32;
    scrollPos++;
    showScroller(scroller,scrollPos/2,true,EFFECT_FADE,CRGB::Blue,CRGB::Green);
    if (scrollPos>160) scrollPos=-16;
  }

	public:
		virtual ~Game(){
		}
		;
    virtual void playGame(){
      if (state==GAME_STATE_SHOW_LEVEL){
        showLevelNumber();
        if (anyKeyClick(0,10))
          state=GAME_STATE_RUNNING;
      }else
        play();
    }
		virtual void play();
		virtual bool needsPlayerSelection(){
			return false;
		}
		virtual void selectPlayer(uint8_t player, bool resetSavedGame){};
};

#endif /* GAME_H_ */
