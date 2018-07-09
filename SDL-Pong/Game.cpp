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
	const char* ballPath = "PongBall.png";
	Texture ballTexture(ballPath, renderer);

	// Load ScoreBoard
	scoreBoardOne = new ScoreBoard(renderer, ScoreBoard::PLAYER_ONE_SCOREBOARD);
	scoreBoardTwo = new ScoreBoard(renderer, ScoreBoard::PLAYER_TWO_SCOREBOARD);

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
	
	// Check if match has endend
	if (player.score > 20 || playerTwo.score > 20)
	{
		Scene *menu = new MainMenu(renderer);
		SceneManager::loadScene(*menu);
		return;
	}

	// Update objects

	// Render background
	backgroundTexture.render(0, 0);

	// Render scoreboard
	scoreBoardOne->update();
	scoreBoardTwo->update();

	// Render Player
	player.updatePosition();
	playerTwo.updatePosition();

	// Render and move ball
	ball.updatePosition();
	ball.move();

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