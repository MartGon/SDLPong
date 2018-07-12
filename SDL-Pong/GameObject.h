#pragma once
#include "Texture.h"
#include "Vector2.h"

class GameObject
{
public:
	GameObject();
	GameObject(Texture texture);
	~GameObject();

	// Active
	bool isActive = true;

	// Render
	bool renderEnabled = true;

	// Collider
	bool colliderEnabled = true;

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
	virtual void onUpdate();
	void update();

	// Collisions
	virtual void calculateColliderBox();
	void computeBoundaries();
	Vector2 getCollisionCenter();

	// Debug
	void drawCollisionBoundaries(SDL_Renderer *renderer);

	// Scale 
	void setScale(Vector2 scale);
};

