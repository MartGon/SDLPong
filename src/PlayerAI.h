#pragma once
#include "Player.h"
#include "Vector2.h"

class PlayerAI : public Player
{
public:
	PlayerAI();
	PlayerAI(Texture texture);
	~PlayerAI();

	MoveDirection getNextMoveDirection(Vector2<float> ballPosition);
};

