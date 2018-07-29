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
#include "Packet.h"
#include <SDL_thread.h>
#include <SDL.h>

//int threadFunction(void *data);

class Game : public Scene
{
public:

	/*
	enum GameMode {
		SINGLE_PLAYER,
		TWO_PLAYERS,
		ONLINE_CLIENT,
		ONLINE_SERVER
	};
	*/

	enum GameState {
		GAME_RUNNING,
		GAME_FINISHED,
		GAME_NETWORK_ERROR
	};

	// Constructors
	Game();
	Game(SDL_Renderer *renderer, SceneMode mode = SINGLE_PLAYER);
	~Game();

	// Game State
	GameState gameState;

	// Win alert
	WinAlert *winAlert = nullptr;

	// Counter
	Counter *counter = nullptr;

	// Players
	Player *player = nullptr;
	PlayerAI *playerTwo = nullptr;

	// Ball
	Ball *ball = nullptr;

	// Scoreboard
	ScoreBoard *scoreBoardOne = nullptr;
	ScoreBoard *scoreBoardTwo = nullptr;

	// Renderer
	SDL_Renderer *renderer = nullptr;

	// Thread
	SDL_Thread *thread = nullptr;
	SDL_sem *sem = nullptr;

	// Game Options
	const Uint8 maxScore = 3;

	// Methods
	void handleConnectionEstablished() override;
	virtual void loadMedia();
	virtual void start();
	virtual void startNewGame();
	virtual void onUpdate();
	virtual void destroy();
	virtual void handleEvent(SDL_Event event);

	// OwnMethods
	void addPointToPlayer(Player* player, Uint8 point = 1);
	bool isGameFinished();
	void handlePossibleFinishedGame();
	void handlePlayersMovement();
	void loadMainMenu();
	void reloadGame();
	//void destroyNetworkAgent();

	// Network
	//bool isOnline();
	/*
	void sendPlayerPositionPacket();
	void sendBallDirection();
	void sendServerData();
	void sendClientData();
	bool handlePacket(Packet *packet);
	void disconnect();
	bool isDisconnected();
	*/
};

