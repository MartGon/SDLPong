#pragma once
#include "Texture.h"
#include "Vector2.h"

class GameObject
{
public:
	GameObject();
	GameObject(Texture texture);
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
	struct ColliderBoundaries
	{
	public:
		int left;
		int right;
		int top;
		int bottom;
	};

	ColliderBoundaries boundaries;

	// Methods

	// Movement
	void updatePosition();

	// Collisions
	void computeBoundaries();
	Vector2 getCollisionCenter();
	void drawCollisionBoundaries(SDL_Renderer *renderer);
};

