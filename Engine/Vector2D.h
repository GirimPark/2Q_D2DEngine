#pragma once
#include <math.h>
#include <cassert>

struct Vector2D
{
	float x;
	float y;

	Vector2D(float x, float y) : x(x), y(y) { }

	Vector2D& operator= (const Vector2D& o)
	{
		this->x = o.x;	this->y = o.y;
		return *this;
	}

	Vector2D operator+ (const Vector2D& o)
	{
		return Vector2D(this->x + o.x, this->y + o.y);
	}

	Vector2D operator- (const Vector2D& o)
	{
		return Vector2D(this->x - o.x, this->y - o.y);
	}

	Vector2D operator* (const Vector2D& o)
	{
		return Vector2D(this->x * o.x, this->y * o.y);
	}

	Vector2D operator/ (const Vector2D& o)
	{
		assert(o.x != 0.f && o.y != 0.f);
		return Vector2D(this->x / o.x, this->y / o.y);
	}

	Vector2D operator/ (float num)
	{
		assert(num != 0.f);
		return Vector2D(this->x / num, this->y / num);
	}

	Vector2D& Normalize()
	{
		float length = sqrt(this->x * this->x + this->y * this->y);
		*this / length;
		return *this;
	}
};