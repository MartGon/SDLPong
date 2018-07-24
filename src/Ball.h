#include "GameObject.h"
#include "Player.h"
#include "Vector2.h"
#include "MainGameLoop.h"
#include <vector>
#pragma once

class Game;
class TextureRenderer;

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
	Collider *collider = nullptr;

	WallCollision checkCollisionWithWalls();
	void handlePossibleWallCollision();
	void modifyDirectionFromCollisionWithPlayer(Player player);
	void onColliderEnter(Collider *collider);

	// Reset
	void reset();

	// Upper Methods
	void onStart() override;
	virtual void onUpdate();

	// Motion Blur
	TextureRenderer *tRenderer = nullptr;
	std::vector<Vector2> motionBlurPositions;
	void renderMotionBlur();
	void addMotionBlurPosition(Vector2 pos);

private:
	
	// Movement
	Vector2 direction;
};

