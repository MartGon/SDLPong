#pragma once
#include "Resources/Texture.h"
#include "../Player/Player.h"
#include "../Ball/Ball.h"

// Constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool initGameWindow(SDL_Window* &window, SDL_Renderer* &renderer);