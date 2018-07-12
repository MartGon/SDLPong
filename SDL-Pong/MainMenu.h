#pragma once
#include "Button.h"
#include "Game.h"
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
	Button *newGameButton;
	Button *exitButton;
	Button *twoPlayersButton;
	std::vector<Button*> buttonList;

	// Renderer
	SDL_Renderer *renderer;

	// Methods
	virtual void loadMedia();
	virtual void onUpdate();
	virtual void handleEvent(SDL_Event event);

	// Own methods
	void handleClickEvent();
	void createGame(Game::GameMode mode);

	// Button methods
	void onClickNewGame();
	void onClickExit();
	void onClickTwoPlayers();
};

