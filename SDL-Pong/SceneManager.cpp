#include "SceneManager.h"

Scene* SceneManager::scene = new Scene();
bool SceneManager::quit = false;

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

void SceneManager::quitGame()
{
	quit = true;
}