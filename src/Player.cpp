#include "Player.h"

// Constructors

Player::Player()
{

}

Player::Player(Texture texture) : GameObject(texture)
{
	speed = 5;
	score = 0;
}

Player::~Player()
{

}

// Methods

void Player::move(Player::MoveDirection direction) 
{
	if (direction == Player::MoveDirection::MOVE_UP)
	{
		if(position.y > 0)
			position.y -= speed;
	}
	else
	{
		if(position.y < 480 - mColliderBox.h)
			position.y += speed;
	}
}

void Player::addPoint()
{
	score++;
	scoreBoard->setScore(score);
}

void Player::resetScore()
{
	score = 0;
	scoreBoard->setScore(score);
}