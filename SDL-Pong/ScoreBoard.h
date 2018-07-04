#pragma once
#include "ScoreBoardNumberDisplay.h"
#include "Vector2.h"
#include <vector>
#include <SDL.h>

class ScoreBoard
{
public:
	enum PlayerScoreBoard
	{
		PLAYER_ONE_SCOREBOARD,
		PLAYER_TWO_SCOREBOARD
	};

	ScoreBoard();
	ScoreBoard(SDL_Renderer* renderer, PlayerScoreBoard scoreboardType);
	~ScoreBoard();

	PlayerScoreBoard scoreboardType;

	// Renderer
	SDL_Renderer *renderer;

	// Displays
	std::vector<ScoreBoardNumberDisplay*> scoreBoardNumberDisplayVector;

	// Methods
	void setScore(int score);
	void update();
};

