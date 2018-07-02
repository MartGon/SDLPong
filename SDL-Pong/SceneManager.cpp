#include "SceneManager.h"

Scene* SceneManager::scene = new Scene();

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::loadScene(Scene &s)
{
	scene = &s;
	scene->loadMedia();
	scene->start();
}