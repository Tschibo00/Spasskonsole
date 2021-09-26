#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include <Arduino.h>

/*
 * 0 5 10
 * 1 6 11
 * 2 7 12      15
 * 3 8 13   18 16 19
 * 4 9 14      17
 */

#define KEY_1 0
#define KEY_2 5
#define KEY_3 10
#define KEY_4 1
#define KEY_5 6
#define KEY_6 11
#define KEY_7 2
#define KEY_8 7
#define KEY_9 12
#define KEY_0 8
#define KEY_LEVEL 3
#define KEY_GAME 13
#define KEY_RESET 4
#define KEY_STOP 9
#define KEY_PLAYER 14
#define KEY_LEFT 18
#define KEY_UP 15
#define KEY_RIGHT 19
#define KEY_DOWN 17
#define KEY_OK 16

void initKeyboardController();
void scanKeyboard();
bool getKeyStatus(uint8_t key);
bool getKeyClick(uint8_t key);
char getNumberStatus();
char getNumberClick();
bool anyKeyClick(uint8_t first, uint8_t last);

#endif
