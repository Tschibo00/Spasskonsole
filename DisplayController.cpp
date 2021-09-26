#include "DisplayController.h"
#include "font.h"

#define DATA_PIN    13
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
#define BRIGHTNESS          20
#define FRAMES_PER_SECOND  30

CRGB leds[NUM_LEDS];
CRGB copyBuffer[NUM_LEDS];

uint8_t levels8[8]={0,1,2,7,15,40,100,255};
uint8_t levels4[4]={0,4,80,255};

uint8_t displayWait = 1;

void initDisplayController(){
	for (uint8_t i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(copyBuffer, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void displayShow(){
  for (uint8_t y=0;y<8;y++)
    for (uint8_t x=0;x<8;x++)
      copyBuffer[x*8+7-y]=leds[x+y*8];
  FastLED.show();  
}

void clear(CRGB color){
	for (uint8_t i = 0; i < NUM_LEDS; i++)
		leds[i] = color;
}

void copy(const uint8_t *source){
  for (uint8_t i = 0; i < 64; i++)
    leds[i]=getFullColor(source[i]);
}

void showScroller(const char *text, int scrollPos, bool smooth, CRGB color){
  showScroller(text,scrollPos,smooth,false,color);  
}
void showScrollerRainbow(const char *text, int scrollPos, bool smooth){
  showScroller(text,scrollPos,smooth,true,CRGB::Black);
}

void showScroller(const char *text, int scrollPos, bool smooth, uint8_t effect, CRGB color1,CRGB color2){
	int textOffset = scrollPos / 8;
	int charOffset = smooth ? 7 - (scrollPos % 8) : (scrollPos % 8 == 7 ? -15 : 7);// values -15 and 7 are not really confirmed
	clear(CRGB::Black);
  switch(effect){
    case 0:
      showCharacter(text[textOffset], charOffset - 7, color1);
      showCharacter(text[textOffset + 1], charOffset + 1, color1);
      break;
    case 1:
      showCharacter(text[textOffset], charOffset - 7, (scrollPos*16)&255, color1);
      showCharacter(text[textOffset + 1], charOffset + 1, (scrollPos*16)&255, color1);
      break;
    case 2:
      showCharacter(text[textOffset], charOffset - 7, color1,color2);
      showCharacter(text[textOffset + 1], charOffset + 1, color1,color2);
      break;
  }
}

void showScroller(const char *text, int scrollPos, bool smooth, bool rainbow, CRGB color){
  if (rainbow)
    showScroller(text,scrollPos,smooth,EFFECT_RAINBOW,color,color);
  else
    showScroller(text,scrollPos,smooth,EFFECT_NONE,color,color);
}

void showCharacter(unsigned char c, int8_t xOffset, CRGB color){
  showCharacter(c,xOffset,-1,color);
}

void showCharacterRainbow(unsigned char c, int8_t xOffset){// TODO wrong implementation for rainbow
  showCharacter(c,xOffset,true,CRGB::Black);
}

void showCharacter(unsigned char c, int8_t xOffset, int rainbow, CRGB color){
	uint8_t b;
	int8_t x, y;
	unsigned char cc = 0;

  if ((c >= 32) && (c <= 127)) cc = c - 32;
  if ((c >= 0) && (c <= 31)) cc = c +96;

	for (y = 0; y < 8; y++) {
    b = font[cc * 8 + y];
		for (x = 7; x >= 0; x--) {
      if (rainbow>=0)
        color=CHSV((rainbow+y*14)&255,255,255);
			set(x + xOffset, y, b&1?color:CRGB::Black);
			b = b >> 1;
		}
	}
}

void showCharacter(unsigned char c, int8_t xOffset, CRGB colorTop,CRGB colorBottom){
  uint8_t b;
  int8_t x, y;
  unsigned char cc = 0;
  CRGB color;

  if ((c >= 32) && (c <= 127)) cc = c - 32;
  if ((c >= 0) && (c <= 31)) cc = c +96;

  for (y = 0; y < 8; y++) {
    b = font[cc * 8 + y];
    for (x = 7; x >= 0; x--) {
      color=fadeTowardColor(colorTop,colorBottom,y*9);
      set(x + xOffset, y, b&1?color:CRGB::Black);
      b = b >> 1;
    }
  }
}

void showCharacter(unsigned char c){
	showCharacter(c, 0, CRGB::White);
}
/*
void drawLine(int x, int y, int dx, int dy, int steps, char color){
	drawDottedLine(x, y, dx, dy, steps, color, color);
}

void drawDottedLine(int x, int y, int dx, int dy, int steps, char color1, char color2){
	for (int i = 0; i < steps; i++) {
		set(x, y, i % 2 ? color1 : color2);
		x += dx;
		y += dy;
	}
}

void drawRectangle(int x, int y, int width, int height, char color){
	drawLine(x, y, 1, 0, width, color);
	drawLine(x, y + height - 1, 1, 0, width, color);
	drawLine(x, y + 1, 0, 1, height - 2, color);
	drawLine(x + width - 1, y + 1, 0, 1, height - 2, color);
}

void drawBox(int x, int y, int width, int height, char color){
	for (int yy = y; yy < y + height; yy++)
		for (int xx = x; xx < x + width; xx++)
			set(xx, yy, color);
}

void drawFade(char c0, char c1, char c2, char c3, char c4){
	for (char i = 0; i < 4; i++) {
		screen[i] = c0;
		screen[i + 4] = c1;
		screen[i + 8] = c2;
		screen[i + 12] = c3;
		screen[i + 16] = c4;
	}
}
*/
void set(int x, int y, CRGB color){
	if (x >= 0 && x < 8 && y >= 0 && y < 8) leds[y * 8 + x] = color;
}

CRGB get(int x, int y){
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
		return leds[y * 8 + x];
	else
		return CRGB::Black;
}
/*
void fade(char steps){
	for (char i = 0; i < 20; i++)
		screen[i] = screen[i] >> steps;
}

void strike(){
	for (char y = 0; y < 5; y++)
		for (char x = 0; x < 4; x++)
			if (x == y)
				set(x, y, 15);
			else
				screen[y * 4 + x] = screen[y * 4 + x] > 0 ? 2 : 0;
}

char* getPalette(){
	return palette;
}

uint8_t* getScreen(){
	return screen;
}
*/

CRGB getFullColor(uint8_t c){
  uint8_t r=c>>5;
  uint8_t g=(c>>2)&7;
  uint8_t b=c&3;
  return CRGB(levels8[r],levels8[g],levels4[b]);
}

void showDigit37(uint8_t num, CRGB c, uint8_t x){
  switch(num){
    case 0:
      set(x+1,1,c);
      set(x,2,c); set(x+2,2,c);
      set(x,3,c); set(x+2,3,c);
      set(x,4,c); set(x+2,4,c);
      set(x+1,5,c);
      break;
    case 1:
      set(x+1,1,c);
      set(x,2,c); set(x+1,2,c);
      set(x+1,3,c);
      set(x+1,4,c);
      set(x,5,c); set(x+1,5,c); set(x+2,5,c);
      break;
    case 2:
      set(x,1,c); set(x+1,1,c);
      set(x+2,2,c);
      set(x+1,3,c);
      set(x,4,c);
      set(x,5,c); set(x+1,5,c); set(x+2,5,c);
      break;
    case 3:
      set(x,1,c); set(x+1,1,c);
      set(x+2,2,c);
      set(x+1,3,c);
      set(x+2,4,c);
      set(x,5,c); set(x+1,5,c);
      break;
    case 4:
      set(x,1,c);
      set(x,2,c); set(x+2,2,c);
      set(x,3,c); set(x+1,3,c); set(x+2,3,c);
      set(x+2,4,c);
      set(x+2,5,c);
      break;
    case 5:
      set(x,1,c); set(x+1,1,c); set(x+2,1,c);
      set(x,2,c);
      set(x,3,c); set(x+1,3,c);
      set(x+2,4,c);
      set(x,5,c); set(x+1,5,c);
      break;
    case 6:
      set(x+1,1,c); set(x+2,1,c);
      set(x,2,c);
      set(x,3,c); set(x+1,3,c);
      set(x,4,c); set(x+2,4,c);
      set(x+1,5,c);
      break;
    case 7:
      set(x,1,c); set(x+1,1,c); set(x+2,1,c);
      set(x+2,2,c);
      set(x+1,3,c);
      set(x+1,4,c);
      set(x+1,5,c);
      break;
    case 8:
      set(x+1,1,c);
      set(x,2,c); set(x+2,2,c);
      set(x+1,3,c);
      set(x,4,c); set(x+2,4,c);
      set(x+1,5,c);
      break;
    case 9:
      set(x+1,1,c);
      set(x,2,c); set(x+2,2,c);
      set(x+1,3,c); set(x+2,3,c);
      set(x+2,4,c);
      set(x,5,c); set(x+1,5,c);
      break;
  }
}

void showNumber37(int8_t num){
  int8_t n=abs(num);
  bool neg=(num<0);
  if (n>99) n=99;
  showDigit37(n/10, neg?CRGB::Red:CRGB::Green, 0);
  showDigit37(n%10, neg?CRGB::Red:CRGB::Green, 4);
}

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
{
  if( cur == target) return;
  
  if( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}

// Blend one CRGB color toward another CRGB color by a given amount.
// Blending is linear, and done in the RGB color space.
// This function modifies 'cur' in place.
CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
{
  nblendU8TowardU8( cur.red,   target.red,   amount);
  nblendU8TowardU8( cur.green, target.green, amount);
  nblendU8TowardU8( cur.blue,  target.blue,  amount);
  return cur;
}
