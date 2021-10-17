#ifndef BOBBLEGAME_H_
#define BOBBLEGAME_H_

#include "Game.h"

#define BOB_BLK 0
#define BOB_RED 1
#define BOB_BLU 2
#define BOB_YEL 3
#define BOB_GRN 4
#define BOB_PUR 5

#define BOB_F_CHANGER 8
#define BOB_F_STONE 16
#define BOB_F_BAT 32
#define BOB_F_HELMET 64
#define BOB_F_FROZEN 128

#define MAGIC_NONE 6
#define MAGIC_BANG 7
#define MAGIC_JOKER 8
#define MAGIC_CIRCLE 9
#define MAGIC_ROW 10
#define MAGIC_RAY 11
#define MAGIC_RAINBOW 12

class BobbleGame: public Game {
  private:
    uint8_t bobbles[3];
    uint8_t numberBobbles=2;
    int8_t angle;
    uint8_t colDiv=4;
    int8_t flying=-1;

    uint8_t height;
    uint8_t colorMod;
    uint8_t yPos;

    int8_t x0,y0,x1,y1;

    uint8_t screen[8*40];
    bool going[8*40];
    int level;
  
    void initLevel();
    void move();
    CRGB bobbleColor(uint8_t bobble);
    void drawBobble(uint8_t x,uint8_t y,uint8_t bobble);
    void rotateBobble(bool up);
    void shoot();
    void initBobble(uint8_t i);
    void drawScreen();
    uint16_t getConnected(int8_t x, int16_t y, uint8_t bobble);
    uint16_t getConnectedBobbles(int8_t x, int16_t y, uint8_t bobble,uint8_t recursion);
    bool getConnectedBobble(int8_t x, int16_t y, uint8_t bobble,uint8_t recursion);

  public:
    BobbleGame();
    void play() override;
    bool needsPlayerSelection() override{
      return true;
    }
};

#endif
