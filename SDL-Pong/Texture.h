#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Vector2.h"

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

	// Scale
	Vector2 scale;

	// Methods

	void render(int x, int y);
	void setAlpha(Uint8 alpha);
	Uint8 getAlpha();
	void free();
};

