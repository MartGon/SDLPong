#pragma once
#include <math.h>

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	Vector2(float x, float y);
	~Vector2();

	// Coordinates
	float x;
	float y;

	// Methods
	void normalize();
	float getModule();
};

// Operators
template <typename T>
Vector2 operator*(const Vector2 &vector, const T &value)
{
	int sX = vector.x * value;
	int sY = vector.y * value;

	return Vector2(sX, sY);
}

Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
