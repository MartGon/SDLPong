#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(const char* resourcePath, SDL_Surface* screenSurface)
{

	SDL_Surface *imgSurface = IMG_Load(resourcePath);
	if (!imgSurface)
	{
		printf("Unable to load png file from %s! SDL Error: %s \n", resourcePath, SDL_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(imgSurface, screenSurface->format, NULL);

		if (!optimizedSurface)
		{
			printf("Unable to optimize surface from %s! SDL Error : %s \n", resourcePath, SDL_GetError());
		}

		SDL_FreeSurface(imgSurface);
	}
}

Texture::Texture(const char* resourcePath, SDL_Renderer* renderer)
{
	path = (char *)resourcePath;

	SDL_Surface *imgSurface = IMG_Load(resourcePath);
	if (!imgSurface)
	{
		printf("Unable to load png file from %s! SDL Error: %s \n", resourcePath, SDL_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		if (!mTexture)
		{
			printf("Unable to optimize surface from %s! SDL Error : %s \n", resourcePath, SDL_GetError());
		}
		else
		{
			mWidth = imgSurface->w;
			mHeight = imgSurface->h;
			mRenderer = renderer;
			scale = Vector2<float>(1, 1);
		}

		SDL_FreeSurface(imgSurface);
	}
}

Texture::~Texture()
{
	//free();
}

// Methods

void Texture::render(int x, int y)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	renderQuad.w *= scale.x;
	renderQuad.h *= scale.y;

	if (0 > SDL_RenderCopy(mRenderer, mTexture, NULL, &renderQuad))
	{
		printf("SDL_RenderCopy: %s\n", SDL_GetError());
		return;
	}

}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

Uint8 Texture::getAlpha()
{
	Uint8 alpha;
	SDL_GetTextureAlphaMod(mTexture, &alpha);

	return alpha;
}

void Texture::free()
{
	//printf("Freeing texture %s\n", path);
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}