#pragma once
#include <SDL.h>
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	Scene();
	Scene(SDL_Renderer* renderer);
	~Scene();

	// Scene state
	bool isPaused = false;

	// Renderer
	SDL_Renderer *renderer;

	// GameObject list
	std::vector<GameObject*> gameObjectList;

	// Overrided Methods
	virtual void loadMedia();
	virtual void start();
	virtual void onUpdate();
	virtual void destroy();
	virtual void handleEvent(SDL_Event event);

	void addGameObject(GameObject *gameObject);
	void update();
	void deactivateAllGameObjects();
	void activateAllGameObjects();
};

