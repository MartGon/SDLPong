#include "PlayerAI.h"



PlayerAI::PlayerAI()
{
}

PlayerAI::PlayerAI(Texture texture) : Player(texture)
{

}

PlayerAI::~PlayerAI()
{
}

Player::MoveDirection PlayerAI::getNextMoveDirection(Vector2 ballPosition)
{
	if (position.y > ballPosition.y)
		return MOVE_UP;
	else
		return MOVE_DOWN;
}