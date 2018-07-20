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
		if(yPos > 0)
			yPos -= speed;
	}
	else
	{
		if(yPos < 480 - mColliderBox.h)
			yPos += speed;
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