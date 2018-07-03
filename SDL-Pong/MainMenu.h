#pragma once
#include "Button.h"
#include "Scene.h"
#include <vector>

class MainMenu : public Scene
{
public:
	MainMenu();
	MainMenu(SDL_Renderer *renderer);
	~MainMenu();

	// Textures
	Texture backgroundTexture;
	Texture gameTitle;

	// Widgets
	Button newGameButton;
	Button exitButton;
	std::vector<Button*> buttonList;

	// Renderer
	SDL_Renderer *renderer;

	// Methods
	virtual void loadMedia();
	virtual void update();
	virtual void handleEvent(SDL_Event event);

	// Own methods
	void handleClickEvent();

	// Button methods
	void onClickNewGame();
	void onClickExit();
};

