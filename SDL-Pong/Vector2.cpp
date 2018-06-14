#include "Vector2.h"

// Constructors

Vector2::Vector2()
{
}

Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{
}

// Methods

void Vector2::normalize()
{
	float mod = getModule();
	x /= mod;
	y /= mod;
}

float Vector2::getModule()
{
	return sqrt(x * x + y * y);
}
