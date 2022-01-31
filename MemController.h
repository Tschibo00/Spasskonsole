#ifndef MEMCONTROLLER_H_
#define MEMCONTROLLER_H_

#include <Arduino.h>

void openGame(char *gameName, uint8_t player);
void put(char *key,int32_t value);
int32_t get(char *key);
void closeGame();

#endif
