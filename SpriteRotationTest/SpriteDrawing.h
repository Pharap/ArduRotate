#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

#include <Arduboy2.h>

#include "Trig.h"
#include "Affine.h"

constexpr unsigned char bitTable[] PROGMEM
{
	(1 << 0),
	(1 << 1),
	(1 << 2),
	(1 << 3),
	(1 << 4),
	(1 << 5),
	(1 << 6),
	(1 << 7),
};

inline uint8_t GetBitMask(uint8_t bit)
{
	return pgm_read_byte(&bitTable[bit % 8]);
}

inline void drawSprite(const uint8_t * bitmap, Vector2 position, Vector2 anglePoint, Brads angle, uint8_t frame)
{
	if (bitmap == nullptr)
		return;
	
	uint8_t width = pgm_read_byte(bitmap++);
	uint8_t height = pgm_read_byte(bitmap++);
	uint8_t halfWidth = width / 2;
	uint8_t halfHeight = height / 2;

	unsigned int frame_offset = 0;

	unsigned int HeightChunks = ( (height / 8) + ( ((height % 8) == 0) ? 0 : 1));

	if(frame > 0)
	{
		frame_offset = (width * HeightChunks);
		bitmap += frame * frame_offset;
	}
	
	unsigned int WidthOffs = 0;
	unsigned int HeightOffs = 0;
	
	for(uint8_t y = 0; y < HeightChunks; y++)
	{
		for(uint8_t x = 0; x < width; x++)
		{
			uint8_t bits = pgm_read_byte(&bitmap[x + WidthOffs]);
			
			if(bits == 0)
				continue;
		
			for(uint8_t bitcount = 0; bitcount < 8; bitcount++)
			{
				if((GetBitMask(bitcount) & bits) == 0)
					continue;
					
				const Vector2 vector1 = (position + Vector2(x, HeightOffs + bitcount));
				const Vector2 vector2 = AffineRotation(vector1, anglePoint + Vector2(halfWidth, halfHeight), angle);
				
				Arduboy2::drawPixel(vector2.x.getInteger(), vector2.y.getInteger(), WHITE);
			}
		}
		
		WidthOffs += width;
		HeightOffs += 8;
	}
}
