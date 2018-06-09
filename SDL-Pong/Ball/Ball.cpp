#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Texture texture)
{
	this->texture = texture;
	speed = 10;

	mColliderBox.w = 42;
	mColliderBox.h = 42;
}

Ball::~Ball()
{
}

// Methods

void Ball::move()
{
	if(xPos > -texture.mWidth)
		xPos -= speed;

	if (checkCollisionWithPlayer(*player) || checkCollisionWithPlayer(*playerTwo))
		speed = -speed;
	else
		return;
}

bool Ball::checkCollisionWithPlayer(Player player)
{
	printf("Comprobando colisiones\n");
	int leftB, leftP;
	int rightB, rightP;
	int topB, topP;
	int bottomB, bottomP;

	leftB = xPos;
	rightB = xPos + mColliderBox.w;
	topB = yPos;
	bottomB = yPos + mColliderBox.h;

	printf("Leftb %i rigthb %i", leftB, rightB);

	leftP = player.xPos;
	rightP = player.xPos + player.mColliderBox.w;
	topP = player.yPos;
	bottomP = player.yPos + player.mColliderBox.h;

	printf("LeftP %i rigthP %i", leftP, rightP);

	if (rightB <= leftP)
		return false;
	if (leftB >= rightP)
		return false;
	if (bottomB <= topP)
		return false;
	if (topB >= bottomP)
		return false;

	return true;
}