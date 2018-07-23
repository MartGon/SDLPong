#pragma once
#include "GameObject.h"
#include "ScoreBoard.h"
#include "Collider.h"

class Player : public GameObject{

public:
	Player();
	Player(Texture texture);
	~Player();

	// Movement
	enum MoveDirection
	{
		MOVE_UP,
		MOVE_DOWN
	};

	// Player score
	int score;

	// Player Scoreboard
	ScoreBoard *scoreBoard = nullptr;

	// Collider
	Collider *collider = nullptr;

	// Methods
	void move(MoveDirection direction);
	void addPoint();
	void resetScore();

	void onStart() override;
};
