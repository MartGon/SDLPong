#include "MainGameLoop.h"

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

			backgroundTexture.render(0, 0);
			//playerTexture.render(20, WINDOW_HEIGHT/2 - playerTexture.mHeight/2);
			player.updatePosition();
			playerTwo.updatePosition();
			SDL_RenderPresent(renderer);
		}
	}

	return 0;
}
