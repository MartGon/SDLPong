#include "Game.h"
#include "Vector2.h"


Game::Game()
{
}

Game::Game(SDL_Renderer * renderer)
{
	this->renderer = renderer;
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

	player = Player(playerTexture);
	playerTwo = Player(playerTexture);
	ball = Ball(ballTexture);
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

	if (currentKeyStates[SDL_SCANCODE_W])
	{
		player.move(player.MOVE_UP);
	}
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		player.move(player.MOVE_DOWN);
	}
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		playerTwo.move(player.MOVE_UP);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		playerTwo.move(player.MOVE_DOWN);
	}

	// Render background
	backgroundTexture.render(0, 0);

	// Render Player
	player.updatePosition();
	playerTwo.updatePosition();
	//player.drawCollisionBoundaries(renderer);
	//playerTwo.drawCollisionBoundaries(renderer);

	// DEbug
	Vector2 playerCentre = player.getCollisionCenter();
	//SDL_RenderDrawLine(renderer, player.boundaries.left, playerCentre.y, player.boundaries.right, playerCentre.y);

	// Render and move ball
	ball.move();
	ball.updatePosition();
	//ball.drawCollisionBoundaries(renderer);

	Vector2 ballCentre = ball.getCollisionCenter();
	//SDL_RenderDrawLine(renderer, ball.boundaries.left, ballCentre.y, ball.boundaries.right, ballCentre.y);
}