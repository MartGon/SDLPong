#include "GameObject.h"
#include "Texture.h"
#include "Player.h"
#include "Vector2.h"
#include "MainGameLoop.h"
#pragma once

class Ball : public GameObject
{
public:
	Ball();
	Ball(Texture texture);

	~Ball();

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

		// Collisions
	enum WallCollision
	{
		NONE_WALL_COLLISION,
		TOP_WALL_COLLISION,
		BOTTOM_WALL_COLLISION,
		LEFT_WALL_COLLISION,
		RIGTH_WALL_COLLISION
	};

	void checkCollisions();
	WallCollision checkCollisionWithWalls();
	bool checkCollisionWithPlayer(Player player);
	void modifyDirectionFromCollisionWithPlayer(Player player);


private:
	
	// Movement
	Vector2 direction;
};

