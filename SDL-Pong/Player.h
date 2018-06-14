#pragma once
#include "Texture.h"
#include "GameObject.h"

class Player : public GameObject{

public:
	Player();
	Player(Texture texture);
	~Player();

	// Movement
	enum MoveDirection
	{
		MOVE_UP,
		MOVE_DOWN
	};

	// Methods

	void move(MoveDirection direction);
};
