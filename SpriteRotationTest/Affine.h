#pragma once
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include "Trig.h"
#define fixed SQ7x8

struct Vec2{
  fixed X,Y;
};

Vec2 AffineTransform(Vec2 Position, Vec2 Transform){
  Vec2 New;
  New.X = Position.X + Transform.X;
  New.Y = Position.Y + Transform.Y;
  return New;
}

Vec2 AffineRotation(Vec2 Position, Vec2 Center ,uint8_t Angle){
  Vec2 New;
  float CosAngle = (float)Cos(Angle);
  float SinAngle = (float)Sin(Angle);
  
  Position = AffineTransform(Position, {-Center.X,-Center.Y});
  
  New.X = ((float)Position.X * CosAngle) - ((float)Position.Y * SinAngle);
  New.Y = ((float)Position.X * SinAngle) + ((float)Position.Y * CosAngle);

  New = AffineTransform(New, {Center.X, Center.Y});
  return New;
}
