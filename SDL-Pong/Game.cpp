#include "Game.h"
#include "Vector2.h"
#include "SceneManager.h"
#include "MainMenu.h"



Game::Game()
{
}

Game::Game(SDL_Renderer * renderer)
{
	this->renderer = renderer;
	gameMode = SINGLE_PLAYER;
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

	scoreboardOne = ScoreBoard(renderer);
	scoreboardTwo = ScoreBoard(renderer);

	player = Player(playerTexture);
	playerTwo = PlayerAI(playerTexture);
	ball = Ball(ballTexture);
}

void Game::startNewGame()
{
	// Set player positions
	player.xPos = 20;
	player.yPos = WINDOW_HEIGHT / 2 - player.texture.mHeight / 2;
	playerTwo.xPos = WINDOW_WIDTH - 20 - playerTwo.texture.mWidth;
	playerTwo.yPos = WINDOW_HEIGHT / 2 - playerTwo.texture.mHeight / 2;

	// Set scoreboards
	scoreboardTwo.xPos = WINDOW_WIDTH / 2 + scoreboardOne.texture.mWidth / 2;
	scoreboardTwo.yPos = scoreboardOne.texture.mHeight / 3;

	scoreboardOne.xPos = WINDOW_WIDTH / 2 - 3 * scoreboardTwo.texture.mWidth / 2;
	scoreboardOne.yPos = scoreboardTwo.texture.mHeight / 3;
	
	// Set up Ball
	ball.player = &player;
	ball.playerTwo = &playerTwo;

	// ResetBall
	ball.reset();
	printf("Primer Reset\n");
}

void Game::start()
{
	startNewGame();
}

void Game::update()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_W])
	{
		player.move(player.MOVE_UP);
	}
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		player.move(player.MOVE_DOWN);
	}
	
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
	else
	{
		Vector2 ballPosition(ball.xPos, ball.yPos);
		Player::MoveDirection nextMove = playerTwo.getNextMoveDirection(ballPosition);
		playerTwo.move(nextMove);
	}
	

	if (player.score > 9 || playerTwo.score > 9)
	{
		Scene *menu = new MainMenu(renderer);
		SceneManager::loadScene(*menu);
		return;
	}

	// Render background
	backgroundTexture.render(0, 0);

	// Render scoreboard
	scoreboardOne.setScore(player.score);
	scoreboardTwo.setScore(playerTwo.score);
	scoreboardOne.updatePosition();
	scoreboardTwo.updatePosition();

	// Render Player
	player.updatePosition();
	playerTwo.updatePosition();

	// Render and move ball
	ball.updatePosition();
	ball.move();

	// Debug Colliders

	/*Vector2 playerCentre = player.getCollisionCenter();
	player.drawCollisionBoundaries(renderer);
	playerTwo.drawCollisionBoundaries(renderer);
	SDL_RenderDrawLine(renderer, player.boundaries.left, playerCentre.y, player.boundaries.right, playerCentre.y);
	ball.drawCollisionBoundaries(renderer);
	Vector2 ballCentre = ball.getCollisionCenter();
	SDL_RenderDrawLine(renderer, ball.boundaries.left, ballCentre.y, ball.boundaries.right, ballCentre.y);*/
}