#include "MemController.h"

#include "Preferences.h"

Preferences preferences;

void openGame(char *gameName, uint8_t player){
  char gn[15];
  uint8_t i;
  for(i=0;i<strlen(gameName);i++)
    gn[i]=gameName[i];
  gn[i]=player+48;
  gn[i+1]=0;
  preferences.begin(gn,false);
}

void put(char *key,int32_t value){
  preferences.putLong(key,value);
}

int get(char *key){
  preferences.getLong(key);
}

void closeGame(){
  preferences.end();
}
