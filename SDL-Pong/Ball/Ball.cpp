#include "Ball.h"

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
				break;

			default:
				break;
		}
	}
	// TODO - Limpiar esto
	else if (checkCollisionWithPlayer(*player))
	{
		direction.x = -direction.x;
		float xDiff = (*player).boundaries.right - boundaries.left;
		float yDiff = 0;
		Vector2 offset(xDiff, yDiff);
		fixPositionAfterCollision(offset);
	}
	else if (checkCollisionWithPlayer(*playerTwo))
	{
		float xDiff = (*playerTwo).boundaries.left - boundaries.right;
		float yDiff = 0;
		Vector2 offset(xDiff, yDiff);
		fixPositionAfterCollision(offset);

		direction.x = -direction.x;
	}
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

void Ball::fixPositionAfterCollision(Vector2 offset)
{
	xPos += offset.x;
	yPos += offset.y;
}

void Ball::setDirection(Vector2 vector2)
{
	vector2.normalize();
	direction = vector2;
}