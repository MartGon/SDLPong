#include "MainMenu.h"
#include "MainGameLoop.h"
#include "Button.h"
#include "Game.h"
#include "SceneManager.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(SDL_Renderer *renderer)
{
	this->renderer = renderer;
}

MainMenu::~MainMenu()
{
}

void MainMenu::loadMedia()
{
	printf("Laoding media\n");

	// Load background
	const char* backgroundPath = "MenuBackGround.png";
	backgroundTexture = Texture(backgroundPath, renderer);

	// Load title
	const char* titlePath = "PongTitle.png";
	gameTitle = Texture(titlePath, renderer);

	// Load  newGame button
	const char* buttonPath = "NewGameButton.png";
	Texture newGameButtonTexture = Texture(buttonPath, renderer);
	newGameButton = Button(newGameButtonTexture);
	newGameButton.xPos = WINDOW_WIDTH / 2 - newGameButton.texture.mWidth / 2;
	newGameButton.yPos = WINDOW_HEIGHT / 3;

	newGameButton.setOnClickListener(std::bind(&MainMenu::onClickNewGame, this));

	// Load  exitGame button
	const char* exitPath = "ExitButton.png";
	Texture exitGameButtonTexture = Texture(exitPath, renderer);
	exitButton = Button(exitGameButtonTexture);
	exitButton.xPos = WINDOW_WIDTH / 2 - newGameButton.texture.mWidth / 2;
	exitButton.yPos = WINDOW_HEIGHT / 2;

	exitButton.setOnClickListener(std::bind(&MainMenu::onClickExit, this));

	// Add them to the list
	buttonList.push_back(&newGameButton);
	buttonList.push_back(&exitButton);
}

void MainMenu::update()
{
	backgroundTexture.render(0, 0);

	gameTitle.render(WINDOW_WIDTH / 2 - gameTitle.mWidth / 2, WINDOW_HEIGHT / 64);

	for (auto button : buttonList)
		button->updatePosition();
}

void MainMenu::handleEvent(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			handleClickEvent();
			break;
		default:
			break;
	}
}

void MainMenu::handleClickEvent()
{
	// Get Mouse coordinates
	int x, y;
	SDL_GetMouseState(&x, &y);

	// Check if any button was pressed
	for (auto const &button : buttonList)
	{
		if (button->isWithinBoundaries(x, y))
		{
			button->onClick();
			break;
		}
	}
}

void MainMenu::onClickNewGame()
{
	Scene *scene = new Game(renderer);
	SceneManager::loadScene(*scene);
}

void MainMenu::onClickExit()
{
	SceneManager::quitGame();
}