#pragma once
#include "../MainGame/Resources/Texture.h"

class Player{

public:
	Player(Texture texture);

	// Sprite
	Texture texture;

	// Movement
	enum MoveDirection
	{
		MOVE_UP,
		MOVE_DOWN
	};

	// Position

	int xPos;
	int yPos;

	// Movement

	int speed = 5;

	// Methods

	void move(MoveDirection direction);
	void updatePosition();
};
