#include <Arduboy2.h>

#include "Bitmaps.h"
#include "SpriteDrawing.h"

Arduboy2 arduboy;

void setup()
{
	arduboy.begin();
}

uint8_t angle = 0;

void loop()
{
	if(!arduboy.nextFrame())
	return;

	arduboy.pollButtons();
	arduboy.clear();  

	if(arduboy.pressed(A_BUTTON))
		++angle;

	if(arduboy.pressed(B_BUTTON))
		--angle;

	drawSprite(Tile, { 32, 32 }, { 32, 32 }, angle, 0);
	drawSprite(Tile, { 48, 32 }, { 32, 32 }, angle, 0);

	arduboy.display();
}
