#include <Arduboy2.h>
Arduboy2 ard;
#include "Bitmaps.h"
#include "SpriteDrawing.h"

void setup() {
  ard.begin();
}

uint8_t rot;

void loop() {
  if(!ard.nextFrame())
    return;
    
  
  
  ard.pollButtons();
  ard.clear();  

  if(ard.pressed(A_BUTTON))
    rot++;
  DrawSprite(Tile,Vec2 {32,32},{32,32}, rot, 0);
  DrawSprite(Tile,Vec2 {48,32},{32,32}, rot, 0);
  ard.display();
}
