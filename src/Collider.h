#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider();

	// Collider boundaries
	int cTop = 0;
	int cBottom = 0;
	int cRight = 0;
	int cLeft = 0;

	// Collider dimensions
	int cWidth = 0;
	int cHeight = 0;

	// Methods
	void calculateColliderBox();
	void calculateColliderBoundaries();
};