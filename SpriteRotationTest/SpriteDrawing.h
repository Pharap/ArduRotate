#pragma once
#include "Affine.h"

const unsigned char PROGMEM Bitset[] = {1,2,4,8,16,32,64,128};

uint8_t GetBitMask(uint8_t Bit){
  if(Bit > 7)
    Bit %= 8;

  return pgm_read_byte(Bitset + Bit);
}



void DrawSprite(const uint8_t* bitmap, Vec2 Position,Vec2 RotationPoint, uint8_t Rotation, uint8_t frame){

  if (bitmap == NULL)
     return;
  
  uint8_t width = pgm_read_byte(bitmap++);
  uint8_t height = pgm_read_byte(bitmap++);
  uint8_t widthDiv = width/2;
  uint8_t heightDiv = height/2;
  unsigned int frame_offset;

  unsigned int HeightChunks = ( height / 8 + ( height % 8 == 0 ? 0 : 1));
  if(frame > 0){
    frame_offset = (width * HeightChunks);
    bitmap += frame * frame_offset;
  }
  
  unsigned int WidthOffs = 0;
  unsigned int HeightOffs = 0;
  
  for(uint8_t y = 0; y < HeightChunks; y++)
  {
      for(uint8_t x = 0; x < width; x++)
      {
        uint8_t Bits = pgm_read_byte(bitmap + x + WidthOffs);
        
        if(Bits > 0)
        {
          for(uint8_t bitcount = 0; bitcount < 8; bitcount++)
          {
            
            if((GetBitMask(bitcount) & Bits) > 0)
            {
              Vec2 New = Position;
              
              New = AffineTransform(New, {x, HeightOffs + bitcount});
              New = AffineRotation(New,{widthDiv + RotationPoint.X, heightDiv + RotationPoint.Y}, Rotation);
              ard.drawPixel(New.X.getInteger(), New.Y.getInteger(), WHITE);
            }
          }
        }
      }
    WidthOffs += width;
    HeightOffs += 8;
  }
}
