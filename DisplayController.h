#ifndef DISPLAY_CONTROLLER
#define DISPLAY_CONTROLLER

#include <Arduino.h>

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
//FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

void initDisplayController();
void displayShow();
void clear(CRGB color);
void copy(const CRGB *source);
/*void copy(const char *source);
void showDigit(char row, char number);
void showNumber(int number);*/
void showScroller(const char *text, int scrollPos, bool smooth, CRGB color);
void showScrollerRainbow(const char *text, int scrollPos, bool smooth);
void showScroller(const char *text, int scrollPos, bool smooth, bool rainbow, CRGB color);

void showCharacter(unsigned char c);
void showCharacter(unsigned char c, int8_t xOffset, CRGB color);
void showCharacterRainbow(unsigned char c, int8_t xOffset);
void showCharacter(unsigned char c, int8_t xOffset, int rainbow, CRGB color);

CRGB getFullColor(uint8_t c);

/*void drawLine(int x, int y, int dx, int dy, int steps, char color);
void drawDottedLine(int x, int y, int dx, int dy, int steps, char color1, char color2);
void drawRectangle(int x, int y, int width, int height, char color);
void drawBox(int x, int y, int width, int height, char color);
void drawFade(char c0, char c1, char c2, char c3, char c4);*/
void set(int x, int y, CRGB color);
CRGB get(int x, int y);
/*void fade(char steps);
void strike();
char* getPalette();
uint8_t* getScreen();*/

#endif
