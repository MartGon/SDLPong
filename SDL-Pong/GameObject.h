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

	// Methods

	void updatePosition();
};

