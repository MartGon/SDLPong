#pragma once
#include "MainGame/Resources/Texture.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	// Sprite
	Texture texture;

	// Position

	int xPos;
	int yPos;

	// Movement

	int speed = 5;

	// Collider 
	SDL_Rect mColliderBox;

	// Boundaries

	struct BallBoundaries
	{
	public:
		int left;
		int right;
		int top;
		int bottom;
	};

	BallBoundaries boundaries;

	// Methods

	// Movement
	void updatePosition();

	// Collisions
	void computeBoundaries();
};

