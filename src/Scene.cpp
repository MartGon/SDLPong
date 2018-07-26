#include "Scene.h"
#include <stdio.h>

// Constructors

Scene::Scene()
{
}

Scene::Scene(SDL_Renderer* renderer)
{

}

Scene::~Scene()
{
}

// Virtual Methods

void Scene::loadMedia() 
{
	printf("Base class\n");
}

void Scene::start()
{

}

void Scene::onUpdate()
{

}

void Scene::destroy()
{
	printf("Destroying scene\n");
	for (auto &gameObject : gameObjectsToInitialize)
		gameObject->destroy();

	for (auto &gameObject : gameObjectList)
		gameObject->destroy();

	this->~Scene();
}

void Scene::handleEvent(SDL_Event event)
{

}

// Methods

void Scene::addGameObject(GameObject *gameObject)
{
	gameObjectsToInitialize.push_back(gameObject);
}

void Scene::initGameObject(GameObject *gameObject)
{
	gameObject->start();

	gameObjectsToInitialize.erase(gameObjectsToInitialize.begin());
	gameObjectList.push_back(gameObject);
}

void Scene::update()
{
	// Return if paused
	if (isPaused)
		return;

	// Init gameObjects
	// This loops allows the list to be altered during the gameObjects' initialization
	while (!gameObjectsToInitialize.empty())
		initGameObject(gameObjectsToInitialize.front());

	// Update every object
	for (int i = 0; i < gameObjectList.size(); i++)
		if(GameObject *gameObject = gameObjectList.at(i))
			if(gameObject->isActive)
				gameObject->update();

	// Update hook
	onUpdate();
}

void Scene::deactivateAllGameObjects()
{
	for (auto gameObject : gameObjectList)
			gameObject->isActive = false;
}

void Scene::activateAllGameObjects()
{
	for (auto gameObject : gameObjectList)
		gameObject->isActive = true;
}