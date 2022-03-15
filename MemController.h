#ifndef MEMCONTROLLER_H_
#define MEMCONTROLLER_H_

#include <Arduino.h>

/*
 * A WORD OF ADVICE
 * Don't ever call any of these methods from within an interrupt, as the preferences library disables
 * interrupts completely during any operation, thus crashing the ESP32
 */

void openGame(char *gameName, uint8_t player);
void put(char *key,int32_t value);
int32_t get(char *key);
void closeGame();

#endif
