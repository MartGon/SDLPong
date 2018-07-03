#pragma once
#include "Player.h"
#include "Ball.h"
#include "Texture.h"
#include "Scene.h"
#include "ScoreBoard.h"
#include <SDL.h>

class Game : public Scene
{
public:
	Game();
	Game(SDL_Renderer *renderer);
	~Game();

	// Players
	Player player;
	Player playerTwo;

	// Ball
	Ball ball;

	// BackGround Texture
	Texture backgroundTexture;

	// Scoreboard
	ScoreBoard scoreboardOne;
	ScoreBoard scoreboardTwo;

	// Renderer
	SDL_Renderer *renderer;

	// Methods

	virtual void loadMedia();
	virtual void start();
	virtual void startNewGame();
	virtual void update();
};

