#include "Game.h"
#include "Vector2.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "NetworkServer.h"
#include "NetworkClient.h"
#include "TextureRenderer.h"
#include "MainGameLoop.h"
#include "Navigator.h"

Game::Game()
{
}

Game::Game(SDL_Renderer *renderer, SceneMode mode) : Scene (mode)
{
	this->renderer = renderer;
	gameState = GAME_RUNNING;
}

Game::~Game()
{
}

void Game::loadMedia()
{
	// Load background
	const char* backgroundPath = "PongBackGround.png";
	Texture backgroundTexture = Texture(backgroundPath, renderer);
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
	Vector2<float> position = Vector2<float>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	winAlert->setRelativePosition(position);
	winAlert->isActive = false;

	// Load Counter Animation
	counter = new Counter(renderer);
	position = Vector2<float>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	counter->setRelativePosition(position);
	counter->isActive = true;

	// Set scoreboard
	player->scoreBoard = scoreBoardOne;
	playerTwo->scoreBoard = scoreBoardTwo;
	
	// Networking
	playerTwo->updateFromClient = true;
}

void Game::startNewGame()
{
	// Set player positions
	player->transform.position.x = 20;
	player->transform.position.y = WINDOW_HEIGHT / 2 - player->collider->cHeight / 2;
	playerTwo->transform.position.x = WINDOW_WIDTH - 20 - playerTwo->collider->cWidth;
	playerTwo->transform.position.y = WINDOW_HEIGHT / 2 - playerTwo->collider->cHeight / 2;

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
	else if(counter)
		counter->initCycle();
}

void Game::start()
{
	startNewGame();
}

void Game::onUpdate()
{
	// Check if match has endend
	if (!isGameFinished())
	{
		// Has counter animation finished
		if (counter->hasAnimationFinished())
		{
			// Ball Movement

			// Start - Critical Section
            if (isOnline())
                SDL_SemWait(sem);

			if (disconnected)
				loadMainMenu();

			ball->navigator->isEnabled = true;

			// Handle movement
			handlePlayersMovement();
			// End - Critical Section
            if (disconnected)
                SDL_SemPost(sem);

		}
	}

	// Debug Colliders

	//ball->collider->drawCollisionBoundaries(renderer);
}

// Own Methods

void Game::addPointToPlayer(Player *player, Uint8 point)
{
	player->addPoint();
	handlePossibleFinishedGame();
}

bool Game::isGameFinished()
{
    handlePossibleFinishedGame();
	return gameState == GAME_FINISHED;
}

void Game::handlePossibleFinishedGame()
{
	// Check scores
	if (player->score < maxScore && playerTwo->score < maxScore)
		return;

	// Activate win alert
	winAlert->isActive = true;

	// Disable counter
	counter->isActive = false;

	// Killing networkAgent for avoiding issues when replay is pressed
	destroyNetworkAgent();

	// Change game State
	gameState = GAME_FINISHED;
}

void Game::handlePlayersMovement()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// Player One movement
	if (mode != ONLINE_CLIENT)
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

	switch (mode)
	{
	case LOCAL_MULTIPLAYER:
		if (currentKeyStates[SDL_SCANCODE_UP])
			playerTwo->move(player->MOVE_UP);
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
			playerTwo->move(player->MOVE_DOWN);
		break;
	case ONLINE_CLIENT:
		//sendClientData();
		break;
	case ONLINE_SERVER:
		//sendServerData();
		break;
	default:
		Vector2<float> ballPosition(ball->transform.position.x, ball->transform.position.y);
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
				disconnect();
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
	Scene *game = new Game(renderer, mode);
	SceneManager::loadScene(*game);
}

void Game::destroy()
{
	Scene::destroy();
}

void Game::handleConnectionEstablished()
{
	counter->initCycle();
}
// Networking
