#pragma once
#include <math.h>

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	// Coordinates
	float x;
	float y;

	// Methods
	void normalize();
	float getModule();
};

