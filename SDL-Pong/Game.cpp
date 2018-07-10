#include "Game.h"
#include "Vector2.h"
#include "SceneManager.h"
#include "MainMenu.h"

Game::Game()
{
}

Game::Game(SDL_Renderer * renderer, GameMode mode)
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

	// Load player sprite
	const char* playerPath = "Player.png";
	Texture playerTexture(playerPath, renderer);

	// Load ball sprite
	const char* ballPath = "PongBallYellow.png";
	Texture ballTexture(ballPath, renderer);

	// Load ScoreBoard
	scoreBoardOne = new ScoreBoard(renderer, ScoreBoard::PLAYER_ONE_SCOREBOARD);
	scoreBoardTwo = new ScoreBoard(renderer, ScoreBoard::PLAYER_TWO_SCOREBOARD);

	// Load WinAlert
	winAlert = WinAlert(renderer);
	Vector2 position = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	winAlert.setRelativePosition(position);

	player = Player(playerTexture);
	playerTwo = PlayerAI(playerTexture);
	ball = Ball(ballTexture);

	// Set scoreboard
	player.scoreBoard = scoreBoardOne;
	playerTwo.scoreBoard = scoreBoardTwo;
}

void Game::startNewGame()
{
	// Set player positions
	player.xPos = 20;
	player.yPos = WINDOW_HEIGHT / 2 - player.texture.mHeight / 2;
	playerTwo.xPos = WINDOW_WIDTH - 20 - playerTwo.texture.mWidth;
	playerTwo.yPos = WINDOW_HEIGHT / 2 - playerTwo.texture.mHeight / 2;
	
	// Set up Ball
	ball.player = &player;
	ball.playerTwo = &playerTwo;

	// ResetBall
	ball.reset();
}

void Game::start()
{
	startNewGame();
}

void Game::update()
{
	// Update objects
	updateGameObjects();

	// Check if match has endend
	if (isGameFinished())
	{
		winAlert.update();
	}
	else
	{
		// Ball Movement
		ball.move();

		// Handle movement
		handlePlayersMovement();
	}

	// Debug Colliders

	/*
	Vector2 playerCentre = player.getCollisionCenter();
	player.drawCollisionBoundaries(renderer);
	playerTwo.drawCollisionBoundaries(renderer);
	SDL_RenderDrawLine(renderer, player.boundaries.left, playerCentre.y, player.boundaries.right, playerCentre.y);
	ball.drawCollisionBoundaries(renderer);
	Vector2 ballCentre = ball.getCollisionCenter();
	SDL_RenderDrawLine(renderer, ball.boundaries.left, ballCentre.y, ball.boundaries.right, ballCentre.y);*/
}

bool Game::isGameFinished()
{
	if (gameState == GAME_FINISHED)
		return true;

	bool isFinished = false;

	if (isFinished = player.score > 2)
		winAlert.setPlayerNumber(0);
	else if (isFinished = playerTwo.score > 2)
		winAlert.setPlayerNumber(1);

	if (isFinished)
		gameState = GAME_FINISHED;

	return isFinished;
}

void Game::handlePlayersMovement()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// Player One movement
	if (currentKeyStates[SDL_SCANCODE_W])
	{
		player.move(player.MOVE_UP);
	}
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		player.move(player.MOVE_DOWN);
	}

	// Player Two movement
	if (gameMode == TWO_PLAYERS)
	{
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			playerTwo.move(player.MOVE_UP);
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			playerTwo.move(player.MOVE_DOWN);
		}
	}

	// PlayerAI movement
	else
	{
		Vector2 ballPosition(ball.xPos, ball.yPos);
		Player::MoveDirection nextMove = playerTwo.getNextMoveDirection(ballPosition);
		playerTwo.move(nextMove);
	}
}

void Game::updateGameObjects()
{
	// Render background
	backgroundTexture.render(0, 0);

	// Render Player
	player.updatePosition();
	playerTwo.updatePosition();

	// Render and move ball
	ball.updatePosition();

	// Render scoreboard
	scoreBoardOne->update();
	scoreBoardTwo->update();
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