#include "Player.h"

// Constructors

Player::Player()
{

}

Player::Player(Texture texture)
{
	this->texture = texture;
	speed = 5;

	mColliderBox.w = texture.mWidth;
	mColliderBox.h = texture.mHeight;
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
		if(yPos < 480 - texture.mHeight)
			yPos += speed;
	}
}