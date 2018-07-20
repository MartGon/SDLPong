#include "GameObject.h"
#include "Texture.h"
#include "Player.h"
#include "Vector2.h"
#include "MainGameLoop.h"
#include <vector>
#pragma once

class Game;
class Ball : public GameObject
{
public:

	// Collisions
	enum WallCollision
	{
		NONE_WALL_COLLISION,
		TOP_WALL_COLLISION,
		BOTTOM_WALL_COLLISION,
		LEFT_WALL_COLLISION,
		RIGTH_WALL_COLLISION
	};

	// Constructors

	Ball();
	Ball(Texture texture);
	~Ball();

	// Game
	Game* game;

	// Players
	Player *player;
	Player *playerTwo;

	// booles
	bool bHasCollidedWithPlayer = false;
	bool bHasCollidedWithPlayerTwo = false;

	// Methods

	// Movement
	void move();
	void setDirection(Vector2 vector2);
	Vector2 getDirection();

	// Collisions
	void checkCollisions();
	bool checkCollisionWithPlayer(Player player);
	WallCollision checkCollisionWithWalls();
	void modifyDirectionFromCollisionWithPlayer(Player player);

	// Reset
	void reset();

	// Upper Methods
	virtual void calculateColliderBox();
	virtual void onUpdate();

	// Motion Blur
	std::vector<Vector2> motionBlurPositions;
	void renderMotionBlur();
	void addMotionBlurPosition(Vector2 pos);

private:
	
	// Movement
	Vector2 direction;
};

