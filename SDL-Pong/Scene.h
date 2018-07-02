#pragma once
#include <SDL.h>

class Scene
{
public:
	Scene();
	Scene(SDL_Renderer* renderer);
	~Scene();

	// Renderer
	SDL_Renderer *renderer;

	// Overrided Methods
	virtual void loadMedia();
	virtual void start();
	virtual void update();
	virtual void destroy();
	virtual void handleEvent(SDL_Event event);
};

