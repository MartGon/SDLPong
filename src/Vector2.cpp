#include "Vector2.h"

// Constructors

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int x, int y)
{
	this->x = (float)x;
	this->y = (float)y;
}

Vector2::Vector2(float x, float y)
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

// Operator

Vector2 operator+(const Vector2 &v1, const Vector2 &v2)
{
	int fX = v1.x + v2.x;
	int fY = v1.y + v2.y;

	return Vector2(fX, fY);
}