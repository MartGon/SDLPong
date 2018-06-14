#include "../GameObject.h"
#include "../MainGame/Resources/Texture.h"
#include "../Player/Player.h"
#include "../Vector2.h"
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
	void fixPositionAfterCollision(Vector2 offset);


private:
	
	// Movement
	Vector2 direction;
};
