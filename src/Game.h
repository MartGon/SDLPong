#pragma once
#include "Player.h"
#include "Ball.h"
#include "Texture.h"
#include "Scene.h"
#include "ScoreBoard.h"
#include "PlayerAI.h"
#include "WinAlert.h"
#include "Counter.h"
#include "NetworkAgent.h"
#include "PongPacket.h"
#include <SDL_thread.h>
#include <SDL.h>

int threadFunction(void *data);

class Game : public Scene
{
public:

	enum GameMode {
		SINGLE_PLAYER,
		TWO_PLAYERS,
		ONLINE_CLIENT,
		ONLINE_SERVER
	};

	enum GameState {
		GAME_RUNNING,
		GAME_FINISHED,
		GAME_NETWORK_ERROR
	};

	// Constructors
	Game();
	Game(SDL_Renderer *renderer, GameMode mode = SINGLE_PLAYER);
	~Game();

	// NetworkManager
	NetworkAgent * networkAgent;

	// Game Mode
	GameMode gameMode;
	bool connectionEstablished = false;

	// Game State
	GameState gameState;

	// Win alert
	WinAlert *winAlert;

	// Counter
	Counter *counter;

	// Players
	Player *player;
	PlayerAI *playerTwo;

	// Ball
	Ball *ball;

	// BackGround Texture
	Texture backgroundTexture;

	// Scoreboard
	ScoreBoard *scoreBoardOne;
	ScoreBoard *scoreBoardTwo;

	// Renderer
	SDL_Renderer *renderer;

	// Thread
	SDL_Thread *thread;
	SDL_sem* sem;

	// Methods
	virtual void loadMedia();
	virtual void start();
	virtual void startNewGame();
	virtual void onUpdate();
	virtual void destroy();
	virtual void handleEvent(SDL_Event event);

	// OwnMethods
	void activateGameObjects();
	bool isGameFinished();
	void handleFinishedGame();
	void handlePlayersMovement();
	void loadMainMenu();
	void reloadGame();
	bool isOnline();
	void destroyNetworkAgent();

	// Network
	void sendPlayerPositionPacket();
	void sendBallDirection();
	void sendServerData();
	void sendClientData();
	bool handlePacket(PongPacket *packet);
	void disconnect();
	bool isDisconnected();
};

