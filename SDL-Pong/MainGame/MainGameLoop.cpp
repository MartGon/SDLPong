#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "MainGameLoop.h"

bool initGameWindow(SDL_Window* &window, SDL_Surface* &surface)
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
	}

	window = SDL_CreateWindow("SDL-Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	return true;
}

int main(int argc, char* args[])
{
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;

	if (!initGameWindow(window, surface))
	{
		printf("Failed to init");
	}
	else
	{
		// Load background
		printf("Loading");
		SDL_Surface *ImgSurface = IMG_Load("PongBackGround.png"); 
		SDL_BlitSurface(ImgSurface, NULL, surface, NULL);
		if (surface == NULL) 
		{ 
			printf("Unable to load image %s! SDL_image Error: %s\n", "PongBackGround.png", IMG_GetError()); 
		}

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

			SDL_UpdateWindowSurface(window);
		}
	}

	return 0;
}
