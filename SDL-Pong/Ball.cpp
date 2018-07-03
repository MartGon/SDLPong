#include "Ball.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Ball::Ball()
{
}

Ball::Ball(Texture texture) : GameObject(texture)
{
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
				playerTwo->addPoint();
				reset();
				break;
			case RIGTH_WALL_COLLISION:
				player->addPoint();
				reset();
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

	// Window Height
	if (boundaries.bottom >= WINDOW_HEIGHT)
		collision = BOTTOM_WALL_COLLISION;

	// Window Width
	if (boundaries.right >= WINDOW_WIDTH)
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

void Ball::reset()
{
	//  Reset Speed
	speed = 8;

	// Set on the center
	xPos = WINDOW_WIDTH / 2 - texture.mWidth / 2;
	yPos = WINDOW_HEIGHT / 2 - texture.mHeight / 2;

	// Randomize direction
	srand(time(NULL));
	int x = rand() % 100 - 50;
	int y = rand() % 100 - 50;
	Vector2 direction(x, y);
	direction.normalize();

	printf("La direcsión fue x= %f e y = %f\n", direction.x, direction.y);

	if (1 - fabs(direction.y) < 0.2 && fabs(direction.x) < 0.2)
	{
		direction.y = 0.5;
		direction.x = 0.5;
		direction.normalize();
	}
	setDirection(direction);
}
