#include "MemTestGame.h"

MemTestGame::MemTestGame(){
}

void MemTestGame::play(){
	clear(CRGB::Black);

Serial.println("a");

  openGame("bla", 0);
Serial.println("b");
  int32_t bla=get("bla");
Serial.println("c");
  showNumber37(bla);

  bla=bla+1;
  if (bla>99) bla=0;
Serial.println("d");
  put("bla", bla);
Serial.println("e");
  closeGame();
Serial.println("f");
}
