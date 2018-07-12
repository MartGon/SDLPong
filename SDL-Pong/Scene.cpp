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

}

void Scene::handleEvent(SDL_Event event)
{

}

// Methods

void Scene::addGameObject(GameObject *gameObject)
{
	gameObjectList.push_back(gameObject);
}

void Scene::update()
{
	for (auto gameObject : gameObjectList)
		if(gameObject->isActive)
			gameObject->update();

	onUpdate();
}
