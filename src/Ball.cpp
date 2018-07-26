#include "Ball.h"
#include "Game.h"
#include "Collider.h"
#include "TextureRenderer.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Ball::Ball()
{
}

Ball::Ball(Texture texture) : GameObject(texture)
{
	speed = 5;
	collider = new Collider(42, 42);
	collider->offset = Vector2(12, 12);
	setComponent(collider);
	tRenderer = getComponent<TextureRenderer>();
}

Ball::~Ball()
{
}

// Methods

// Movement

void Ball::move()
{
    // Check wall collisions
    handlePossibleWallCollision();

	transform.position.x += (direction.x * speed);
	transform.position.y += (direction.y * speed);

	// Add to motion blur vector
	addMotionBlurPosition(Vector2(transform.position.x, transform.position.y));
}

Vector2 Ball::getDirection()
{
	return direction;
}

void Ball::setDirection(Vector2 vector2)
{
	vector2.normalize();
	direction = vector2;
}

// Collisions

Ball::WallCollision Ball::checkCollisionWithWalls()
{
	WallCollision collision = NONE_WALL_COLLISION;

	if (collider->cTop <= 0)
		collision = TOP_WALL_COLLISION;

	// Window Height
	if (collider->cBottom >= WINDOW_HEIGHT)
		collision = BOTTOM_WALL_COLLISION;

	// Window Width
	if (collider->cRight >= WINDOW_WIDTH)
		collision = RIGTH_WALL_COLLISION;

	if (collider->cLeft <= 0)
		collision = LEFT_WALL_COLLISION;

	//printf("La colision fue %i\n", collision);

	return collision;
}

void Ball::handlePossibleWallCollision()
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
            playerTwo->addPoint();
			game->startNewGame();
			break;
		case RIGTH_WALL_COLLISION:
            player->addPoint();
			game->startNewGame();
			break;

		default:
			break;
		}
	}
}

void Ball::modifyDirectionFromCollisionWithPlayer(Player player)
{
	Vector2 ballCenter = collider->getCollisionCenter();
	Vector2 padCenter = player.collider->getCollisionCenter();

	int ballRelativeYpos = ballCenter.y - padCenter.y;
	float playerMaxValue = (player.collider->cHeight / 2) + collider->cHeight / 2;
	float centerRate = ballRelativeYpos / playerMaxValue;

	direction.x = -direction.x;
	direction.y = centerRate;

	direction.normalize();
	speed += 1;
}

void Ball::onColliderEnter(Collider *collider)
{
	if (Player *player = dynamic_cast<Player*>(collider->gameObject))
	{
		modifyDirectionFromCollisionWithPlayer(*player);
	}
}

// Initializing and stuff

void Ball::reset()
{
	//  Reset Speed
	speed = 6;

	// Reset Motion Blur
	motionBlurPositions.clear();

	// Set on the center
	transform.position.x = WINDOW_WIDTH / 2 - tRenderer->texture.mWidth / 2;
	transform.position.y = WINDOW_HEIGHT / 2 - tRenderer->texture.mHeight / 2;

	// Randomize direction
	srand(time(NULL));
	int x = rand() % 100 - 50;
	int y = rand() % 100 - 50;
	Vector2 direction(x, y);
	direction.normalize();

	//printf("La direcsión fue x= %f e y = %f\n", direction.x, direction.y);

	if (1 - fabs(direction.y) < 0.2 && fabs(direction.x) < 0.2)
	{
		direction.y = 0.5;
		direction.x = 0.5;
		direction.normalize();
	}
	setDirection(direction);
}

void Ball::onStart()
{
	collider = getComponent<Collider>();
	tRenderer = getComponent<TextureRenderer>();
}

void Ball::onUpdate()
{
	renderMotionBlur();
}

// Motion Blur

void Ball::addMotionBlurPosition(Vector2 pos)
{
	motionBlurPositions.push_back(pos);

	// We want just five positions to render 
	if (motionBlurPositions.size() > speed)
		motionBlurPositions.erase(motionBlurPositions.begin());
}

void Ball::renderMotionBlur()
{
	int factor = 128 / (motionBlurPositions.size() + 1);

	for (int i = 0; i < motionBlurPositions.size(); i++)
	{
		Vector2 pos = motionBlurPositions.at(i);
		tRenderer->texture.setAlpha(i * factor);
		tRenderer->texture.render(pos.x, pos.y);
	}
	tRenderer->texture.setAlpha(255);
}