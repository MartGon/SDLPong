#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Texture
{
public:
	// Constructors
	Texture();
	Texture(const char* resourcePath, SDL_Surface* screenSurface);
	Texture(const char* resourcePath, SDL_Renderer* renderer);
	~Texture();
	
	// SDL Stuff
	SDL_Texture *mTexture;
	SDL_Surface *optimizedSurface;
	SDL_Renderer *mRenderer;

	// Dimensions
	int mWidth;
	int mHeight;

	// Methods

	void render(int x, int y);
};

