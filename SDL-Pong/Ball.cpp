#include "Ball.h"
#include <math.h>

Ball::Ball()
{
}

Ball::Ball(Texture texture)
{
	this->texture = texture;
	speed = 8;

	mColliderBox.w = 42;
	mColliderBox.h = 42;
}

Ball::~Ball()
{
}

// Methods

void Ball::move()
{
	// check collisions
	checkCollisions();

	xPos += (direction.x * speed);
	yPos += (direction.y * speed);
}

void Ball::checkCollisions()
{
	bool collisionWithPlayer = checkCollisionWithPlayer(*player);
	bool collisionWithPlayerTwo = checkCollisionWithPlayer(*playerTwo);

	if (WallCollision collision = checkCollisionWithWalls())
	{
		switch (collision)
		{
			case TOP_WALL_COLLISION:
			case BOTTOM_WALL_COLLISION:
				direction.y = -direction.y;
				break;

			case LEFT_WALL_COLLISION:
			case RIGTH_WALL_COLLISION:
				direction.x = -direction.x;
				// Hacer cosas con la puntuación
				xPos = WINDOW_WIDTH / 2 - texture.mWidth / 2;
				yPos = WINDOW_HEIGHT / 2 - texture.mHeight / 2;
				break;

			default:
				break;
		}
	}
	else if (collisionWithPlayer && !bHasCollidedWithPlayer)
	{
		bHasCollidedWithPlayer = true;
		modifyDirectionFromCollisionWithPlayer(*player);
	}
	else if (collisionWithPlayerTwo && !bHasCollidedWithPlayerTwo)
	{
		bHasCollidedWithPlayerTwo = true;
		modifyDirectionFromCollisionWithPlayer(*playerTwo);
	}

	bHasCollidedWithPlayer = collisionWithPlayer;
	bHasCollidedWithPlayerTwo = collisionWithPlayerTwo;
}

bool Ball::checkCollisionWithPlayer(Player player)
{
	
	if (boundaries.right <= player.boundaries.left)
		return false;

	if (boundaries.left >= player.boundaries.right)
		return false;

	if (boundaries.bottom <= player.boundaries.top)
		return false;

	if (boundaries.top >= player.boundaries.bottom)
		return false;

	return true;
}

Ball::WallCollision Ball::checkCollisionWithWalls()
{
	WallCollision collision = NONE_WALL_COLLISION;

	if (boundaries.top <= 0)
		collision = TOP_WALL_COLLISION;

	// Window Width
	if (boundaries.bottom >= 480)
		collision = BOTTOM_WALL_COLLISION;

	// Window height
	if (boundaries.right >= 640)
		collision = RIGTH_WALL_COLLISION;

	if (boundaries.left <= 0)
		collision = LEFT_WALL_COLLISION;

	//printf("La colision fue %i\n", collision);

	return collision;
}

void Ball::setDirection(Vector2 vector2)
{
	vector2.normalize();
	direction = vector2;
}

void Ball::modifyDirectionFromCollisionWithPlayer(Player player)
{
	Vector2 ballCenter = getCollisionCenter();
	Vector2 padCenter = player.getCollisionCenter();

	int ballRelativeYPos = ballCenter.y - padCenter.y;
	float playerMaxValue = (player.mColliderBox.h / 2) + mColliderBox.h / 2;
	float centerRate = ballRelativeYPos / playerMaxValue;

	direction.x = -direction.x;
	direction.y = centerRate;

	direction.normalize();
}