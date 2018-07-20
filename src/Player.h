#pragma once
#include "GameObject.h"
#include "ScoreBoard.h"

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
	ScoreBoard *scoreBoard;

	// Methods

	void move(MoveDirection direction);
	void addPoint();
	void resetScore();
};
