#pragma once
#include "Player.h"
#include "Ball.h"
#include "Texture.h"
#include "Scene.h"
#include "ScoreBoard.h"
#include "PlayerAI.h"
#include "WinAlert.h"
#include <SDL.h>

class Game : public Scene
{
public:

	enum GameMode {
		SINGLE_PLAYER,
		TWO_PLAYERS
	};

	enum GameState {
		GAME_RUNNING,
		GAME_FINISHED,
		GAME_WAITiNG
	};

	// Constructors

	Game();
	Game(SDL_Renderer *renderer, GameMode mode = SINGLE_PLAYER);
	~Game();

	// Game Mode
	GameMode gameMode;

	// Game State
	GameState gameState;

	// Win alert
	WinAlert winAlert;

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
	virtual void handleEvent(SDL_Event event);

	// OwnMethods
	bool isGameFinished();
	void handlePlayersMovement();
	void updateGameObjects();
	void loadMainMenu();
	void reloadGame();
};

