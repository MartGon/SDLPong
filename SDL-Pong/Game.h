#pragma once
#include "Player.h"
#include "Ball.h"
#include "Texture.h"
#include "Scene.h"
#include "ScoreBoard.h"
#include "PlayerAI.h"
#include <SDL.h>

class Game : public Scene
{
public:
	Game();
	Game(SDL_Renderer *renderer);
	~Game();

	// Game Mode

	enum GameMode {
		SINGLE_PLAYER,
		TWO_PLAYERS
	};

	GameMode gameMode;

	// Players
	Player player;
	PlayerAI playerTwo;

	// Ball
	Ball ball;

	// BackGround Texture
	Texture backgroundTexture;

	// Scoreboard
	ScoreBoard *scoreBoardOne;
	ScoreBoard *scoreBoardTwo;

	// Renderer
	SDL_Renderer *renderer;

	// Methods

	virtual void loadMedia();
	virtual void start();
	virtual void startNewGame();
	virtual void update();
};

