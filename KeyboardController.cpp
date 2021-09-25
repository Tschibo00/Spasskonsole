#include "KeyboardController.h"

#define DEBOUNCE 100		// ms for debounce, increase for longer debounce period

int keyLatchPin[5] = { 21,19,18,17,16 };
int keyMatrixPin[4] = { 32,33,26,27 };
bool keyStatus[20];
unsigned long keyLocked[20];
uint8_t scanRow=0;

void initKeyboardController(){
	uint8_t i;
	for (i = 0; i < 5; i++)
		pinMode(keyLatchPin[i], OUTPUT);
	for (i = 0; i < 4; i++)
		pinMode(keyMatrixPin[i], INPUT_PULLDOWN);
	for (i = 0; i < 20; i++)
		keyLocked[i] = millis();
}

void scanKeyboard(){
	uint8_t i;

  // read inputs with the last activated row
	for (i = 0; i < 4; i++)
		keyStatus[i * 5 + scanRow] = digitalRead(keyMatrixPin[i]);

  // increase row and set pins
  scanRow=(scanRow+1)%5;
  for (i = 0; i < 5; i++)
    digitalWrite(keyLatchPin[i], i==scanRow);
}

bool getKeyStatus(uint8_t key){
  if (key>19)
    return false;
  else
  	return keyStatus[key];
}

bool getKeyClick(uint8_t key){
  if (key>19)
    return false;
  else {
  	if (getKeyStatus(key)) {
  		if (keyLocked[key] > millis()) {					// still pressed?
  			keyLocked[key] = millis() + DEBOUNCE;		// set debounce period
  			return false;
  		} else {
  			keyLocked[key] = millis() + DEBOUNCE;		// set debounce period
  			return true;
  		}
  	} else
  		return false;
  }
}

char getNumberStatus(){
	for (uint8_t i = 0; i < 20; i++)
		if (getKeyStatus(i)) return i;
	return -1;
}

char getNumberClick(){
	for (uint8_t i = 0; i < 20; i++)
		if (getKeyClick(i)) return i;
	return -1;
}

bool anyKeyClick(uint8_t first, uint8_t last){
	for (uint8_t i = first; i <= last; i++)
		if (getKeyClick(i)) return true;
	return false;
}
