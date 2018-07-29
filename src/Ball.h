#include "GameObject.h"
#include "Player.h"
#include "Vector2.h"
#include "Navigator.h"
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
	Navigator *navigator = nullptr;

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
	std::vector<Vector2<float>> motionBlurPositions;
	void renderMotionBlur();
	void addMotionBlurPosition(Vector2<float> pos);

	// Hooks
		// Movement
	void beforeMove() override;
	void afterMove() override;
};

