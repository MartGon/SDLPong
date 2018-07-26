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

	// Widgets
	Button *newGameButton;
	Button *exitButton;
	Button *twoPlayersButton;
	Button *onlineButton;

	// Layer 2 Widgets

	Button *serverButton;
	Button *clientButton;
	Button *backButton;

	// Widget list
	std::vector<Button*> buttonList;

	// Renderer
	SDL_Renderer *renderer;

	// Methods
	virtual void loadMedia();
	virtual void onUpdate();
	virtual void handleEvent(SDL_Event event);

	// Own methods
	void activateButtonLayer(Uint8 layer);
	void handleClickEvent();
	void createGame(SceneMode mode);

	// Button methods
	void onClickNewGame();
	void onClickExit();
	void onClickTwoPlayers();
	void onClickOnline();

	// Layer 2 Button Methods
	void onClickServer();
	void onClickClient();
	void onClickBack();
};

