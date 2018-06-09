#include "Player.h"

// Constructors

Player::Player(Texture texture)
{
	this->texture = texture;
}

// Methods

void Player::move(Player::MoveDirection direction) 
{
	if (direction == Player::MoveDirection::MOVE_UP)
	{
		if(yPos > 0)
			yPos -= (1 * speed);
	}
	else
	{
		if(yPos < 480 - texture.mHeight)
			yPos += (1 * speed);
	}
}

void Player::updatePosition()
{
	texture.render(xPos, yPos);
}