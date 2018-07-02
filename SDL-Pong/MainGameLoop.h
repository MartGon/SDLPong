#pragma once
#include "Texture.h"

// Constants
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

enum GameState {

	MENU_GAME_STATE,
	INIT_GAME_GAME_STATE,
	RUNNING_GAME_GAME_STATE
};

bool initGameWindow(SDL_Window* &window, SDL_Renderer* &renderer);

void closeGame();