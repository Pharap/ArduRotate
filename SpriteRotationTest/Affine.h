#pragma once

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include "Trig.h"

struct Vector2
{
	SQ7x8 x;
	SQ7x8 y;
	
	Vector2() = default;
	
	constexpr Vector2(SQ7x8 x, SQ7x8 y) :
		x { x }, y { y }
	{
	}
	
	Vector2 & operator +=(Vector2 other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	
	Vector2 & operator -=(Vector2 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	
	template<typename Number>
	Vector2 & operator *=(Number scale)
	{
		this->x *= scale;
		this->y *= scale;
		return *this;
	}
};

constexpr Vector2 operator -(Vector2 vector)
{
	return { -vector.x, -vector.y };
}

constexpr Vector2 operator +(Vector2 left, Vector2 right)
{
	return { left.x + right.x, left.y + right.y };
}

constexpr Vector2 operator -(Vector2 left, Vector2 right)
{
	return { left.x - right.x, left.y - right.y };
}

template<typename Number>
constexpr Vector2 operator *(Vector2 left, Number right)
{
	return { left.x * right, left.y * right };
}

constexpr Vector2 AffineTransform(Vector2 position, Vector2 transform)
{
	return position + transform;
}

Vector2 AffineRotation(Vector2 position, Vector2 centre, Brads angle)
{
	const auto cosAngle = fixedCos(angle);
	const auto sinAngle = fixedSin(angle);

	const Vector2 newPosition = (position - centre);

	const Vector2 vector =
	{
		(newPosition.x * cosAngle) - (newPosition.y * sinAngle),
		(newPosition.x * sinAngle) + (newPosition.y * cosAngle)
	};

	return AffineTransform(vector, centre);
}