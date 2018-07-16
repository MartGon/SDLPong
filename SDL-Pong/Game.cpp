#include "Game.h"
#include "Vector2.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "NetworkServer.h"
#include "NetworkClient.h"

Game::Game()
{
}

Game::Game(SDL_Renderer *renderer, GameMode mode)
{
	this->renderer = renderer;
	this->gameMode = mode;
	gameState = GAME_RUNNING;
}

Game::~Game()
{
}

void Game::loadMedia()
{
	// Load background
	const char* backgroundPath = "PongBackGround.png";
	backgroundTexture = Texture(backgroundPath, renderer);
	GameObject *background = new GameObject(backgroundTexture);

	// Load player sprite
	const char* playerPath = "player.png";
	Texture playerTexture(playerPath, renderer);

	// Load ball sprite
	const char* ballPath = "PongBallYellow.png";
	Texture ballTexture(ballPath, renderer);

	// Load ScoreBoard
	scoreBoardOne = new ScoreBoard(renderer, ScoreBoard::PLAYER_ONE_SCOREBOARD);
	scoreBoardTwo = new ScoreBoard(renderer, ScoreBoard::PLAYER_TWO_SCOREBOARD);

	// Create GameObjects
	player = new Player(playerTexture);
	playerTwo = new PlayerAI(playerTexture);
	ball = new Ball(ballTexture);

	// Set up Ball
	ball->player = player;
	ball->playerTwo = playerTwo;
	ball->game = this;

	// Load WinAlert
	winAlert = new WinAlert(renderer);
	Vector2 position = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	winAlert->setRelativePosition(position);
	winAlert->isActive = false;

	// Load Counter Animation
	counter = new Counter(renderer);
	position = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	counter->setRelativePosition(position);
	counter->isActive = false;

	// Set scoreboard
	player->scoreBoard = scoreBoardOne;
	playerTwo->scoreBoard = scoreBoardTwo;

	// Creating networkAgents
	if (gameMode == ONLINE_SERVER)
		networkAgent = new NetworkServer();
	else if (gameMode == ONLINE_CLIENT)
		networkAgent = new NetworkClient();
}

void Game::startNewGame()
{
	// Set player positions
	player->xPos = 20;
	player->yPos = WINDOW_HEIGHT / 2 - player->texture.mHeight / 2;
	playerTwo->xPos = WINDOW_WIDTH - 20 - playerTwo->texture.mWidth;
	playerTwo->yPos = WINDOW_HEIGHT / 2 - playerTwo->texture.mHeight / 2;

	// ResetBall
	ball->reset();

	// Start Counter
	if (isOnline())
	{
		if (connectionEstablished)
		{
			counter->initCycle();
		}
	}
	else
		counter->initCycle();
}

void Game::start()
{
	startNewGame();
}

void Game::onUpdate()
{
	// Check if connection is established, in case of online game
	if (isOnline() && !connectionEstablished)
	{
		if (connectionEstablished = networkAgent->establishConnection())
		{
			// Start match
			startNewGame();
		}
	}
	else
	{
		// Check if match has endend
		if (!isGameFinished())
		{
			// Has counter animation finished
			if (counter->hasAnimationFinished())
			{
				// Ball Movement
				ball->move();

				// Handle movement
				handlePlayersMovement();
			}
		}
	}

	// Debug Colliders

	/*
	Vector2 playerCentre = player->getCollisionCenter();
	player->drawCollisionBoundaries(renderer);
	playerTwo->drawCollisionBoundaries(renderer);
	SDL_RenderDrawLine(renderer, player->boundaries.left, playerCentre.y, player->boundaries.right, playerCentre.y);
	ball->drawCollisionBoundaries(renderer);
	Vector2 ballCentre = ball->getCollisionCenter();
	SDL_RenderDrawLine(renderer, ball->boundaries.left, ballCentre.y, ball->boundaries.right, ballCentre.y);*/
}

bool Game::isGameFinished()
{
	bool isFinished = false;

	if (gameState == GAME_FINISHED)
		return true;

	if (isFinished = player->score > 2)
		winAlert->setPlayerNumber(0);
	else if (isFinished = playerTwo->score > 2)
		winAlert->setPlayerNumber(1);

	if (isFinished)
		handleFinishedGame();

	return isFinished;
}

void Game::handleFinishedGame()
{
	gameState = GAME_FINISHED;
	winAlert->isActive = true;
	counter->isActive = false;

	// Killing networkAgent for avoiding issues when replay is pressed
	if(isOnline())
		networkAgent->destroy();
}

void Game::handlePlayersMovement()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// Player One movement
	if (gameMode != ONLINE_CLIENT)
	{
		if (currentKeyStates[SDL_SCANCODE_W])
			player->move(player->MOVE_UP);
		else if (currentKeyStates[SDL_SCANCODE_S])
			player->move(player->MOVE_DOWN);
	}
	// If Online client
	else
	{
		if (currentKeyStates[SDL_SCANCODE_W])
			playerTwo->move(player->MOVE_UP);
		else if (currentKeyStates[SDL_SCANCODE_S])
			playerTwo->move(player->MOVE_DOWN);
	}

	switch (gameMode)
	{
	case TWO_PLAYERS:
		if (currentKeyStates[SDL_SCANCODE_UP])
			playerTwo->move(player->MOVE_UP);
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
			playerTwo->move(player->MOVE_DOWN);
		break;
	case ONLINE_CLIENT:
		sendClientData();
		handlePacket(networkAgent->recvPacket());
		handlePacket(networkAgent->recvPacket());
		break;
	case ONLINE_SERVER:
		sendServerData();
		handlePacket(networkAgent->recvPacket());
		break;
	default:
		Vector2 ballPosition(ball->xPos, ball->yPos);
		Player::MoveDirection nextMove = playerTwo->getNextMoveDirection(ballPosition);
		playerTwo->move(nextMove);
		break;
	}
}

void Game::handleEvent(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				loadMainMenu();
				break;

			case SDLK_e:
				if (gameState == GAME_FINISHED)
					loadMainMenu();
				break;

			case SDLK_r:
				if (gameState == GAME_FINISHED)
					reloadGame();
			default:
				break;
		}
	}
}

void Game::loadMainMenu()
{
	Scene *menu = new MainMenu(renderer);
	SceneManager::loadScene(*menu);
}

void Game::reloadGame()
{
	Scene *game = new Game(renderer, gameMode);
	SceneManager::loadScene(*game);
}

bool Game::isOnline()
{
	return gameMode == ONLINE_SERVER || gameMode == ONLINE_CLIENT;
}

void Game::activateGameObjects()
{
	activateAllGameObjects();
	winAlert->isActive = false;
}

// Networking

void Game::sendPlayerPositionPacket()
{
	PongPacket::PacketType type;
	Vector2 playerPos;

	if (gameMode == ONLINE_SERVER)
	{
		type = PongPacket::PACKET_PLAYER_1_POSITION;
		playerPos = Vector2(player->xPos, player->yPos);
	}
	else
	{
		type = PongPacket::PACKET_PLAYER_2_POSITION;
		playerPos = Vector2(playerTwo->xPos, playerTwo->yPos);
	}

	PongPacket* playerPacket = new PongPacket(type, playerPos);
	networkAgent->sendPacket(playerPacket);
}

void Game::sendBallDirection()
{
	Vector2 ballPos(ball->xPos, ball->yPos);
	PongPacket* ballPacket = new PongPacket(PongPacket::PACKET_BALL_POSITION, ballPos);
	ballPacket->direction = ball->getDirection();
	networkAgent->sendPacket(ballPacket);
}

void Game::sendServerData()
{
	sendPlayerPositionPacket();
	sendBallDirection();
}

void Game::sendClientData()
{
	sendPlayerPositionPacket();
}

void Game::handlePacket(PongPacket* packet)
{
	if (!packet)
	{
		std::cout << "Se perdi� la conexi�n con el otro jugador\n";
		loadMainMenu();
		return;
	}

	switch (packet->packetType)
	{
	case PongPacket::PACKET_BALL_POSITION:
		ball->setDirection(packet->direction);
		ball->xPos = packet->position.x;
		ball->yPos = packet->position.y;
		break;
	case PongPacket::PACKET_PLAYER_1_POSITION:
		player->yPos = packet->position.y;
		break;
	case PongPacket::PACKET_PLAYER_2_POSITION:
		playerTwo->yPos = packet->position.y;
	default:
		break;
	}
}

void Game::destroy()
{
	if (isOnline())
		networkAgent->destroy();

	Scene::destroy();
}