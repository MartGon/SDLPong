#include "MainGameLoop.h"
#include "../Ball/Ball.h"
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool initGameWindow(SDL_Window* &window, SDL_Renderer* &renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Could not initialize SDL Video, Error: %s \n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG; 
	if (!(IMG_Init(imgFlags) & imgFlags)) 
	{ 
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()); 
		return false;
	}

	window = SDL_CreateWindow("SDL-Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Window could not be created! SDL Error: %s \n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

int main(int argc, char* args[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (!initGameWindow(window, renderer))
	{
		printf("Failed to init");
	}
	else
	{
		// Load background
		const char* backgroundPath = "PongBackGround.png";
		Texture backgroundTexture(backgroundPath, renderer);

		// Load player sprite
		const char* playerPath = "Player.png";
		Texture playerTexture(playerPath, renderer);

		Player player(playerTexture);
		player.xPos = 20;
		player.yPos = WINDOW_HEIGHT / 2 - playerTexture.mHeight / 2;

		Player playerTwo(playerTexture);
		playerTwo.xPos = WINDOW_WIDTH - 20 - playerTexture.mWidth;
		playerTwo.yPos = WINDOW_HEIGHT / 2 - playerTexture.mHeight / 2;

		// Load ball sprite

		const char* ballPath = "PongBall.png";
		Texture ballTexture(ballPath, renderer);

		Ball ball(ballTexture);
		ball.xPos = WINDOW_WIDTH / 2 - ballTexture.mWidth / 2;
		ball.yPos = WINDOW_HEIGHT / 2 - ballTexture.mHeight / 2;
		ball.setDirection(Vector2(1, 1));

		ball.player = &player;
		ball.playerTwo = &playerTwo;

		SDL_Event e;

		bool quit = false;
		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_n)
					{
						ball.move();
					}
				}
			}

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

			// Render buffer
			SDL_RenderPresent(renderer);
		}
	}

	return 0;
}
