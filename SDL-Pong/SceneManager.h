#pragma once
#include "Scene.h"

static class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static Scene *scene;

	static void loadScene(Scene& s);
};

