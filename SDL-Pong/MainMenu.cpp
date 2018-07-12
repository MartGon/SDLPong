#include "MainMenu.h"
#include "MainGameLoop.h"
#include "Button.h"
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
	GameObject *background = new GameObject(backgroundTexture);
	background->xPos = 0;
	background->yPos = 0;

	// Load title
	const char* titlePath = "PongTitle.png";
	gameTitle = Texture(titlePath, renderer);
	GameObject *title = new GameObject(gameTitle);
	title->xPos = WINDOW_WIDTH / 2 - gameTitle.mWidth / 2;
	title->yPos = WINDOW_HEIGHT / 64;

	
	// Load  newGame button
	const char* buttonPath = "NewGameButton.png";
	Texture newGameButtonTexture = Texture(buttonPath, renderer);
	newGameButton = new Button(newGameButtonTexture);
	newGameButton->xPos = WINDOW_WIDTH / 2 - newGameButton->texture.mWidth / 2;
	newGameButton->yPos = WINDOW_HEIGHT / 3;

	newGameButton->setOnClickListener(std::bind(&MainMenu::onClickNewGame, this));

	// Load  exitGame button
	const char* exitPath = "ExitButton.png";
	Texture exitGameButtonTexture = Texture(exitPath, renderer);
	exitButton = new Button(exitGameButtonTexture);
	exitButton->xPos = WINDOW_WIDTH / 2 - exitButton->texture.mWidth / 2;
	exitButton->yPos = WINDOW_HEIGHT / 1.5f;

	exitButton->setOnClickListener(std::bind(&MainMenu::onClickExit, this));

	// Load TwoPlayers Button
	const char* twoPlayersPath = "TwoPlayers.png";
	Texture twoPlayersButtonTexture = Texture(twoPlayersPath, renderer);
	twoPlayersButton = new Button(twoPlayersButtonTexture);
	twoPlayersButton->xPos = WINDOW_WIDTH / 2 - twoPlayersButton->texture.mWidth / 2;
	twoPlayersButton->yPos = WINDOW_HEIGHT / 2;

	twoPlayersButton->setOnClickListener(std::bind(&MainMenu::onClickTwoPlayers, this));

	// Add them to the list
	buttonList.push_back(newGameButton);
	buttonList.push_back(twoPlayersButton);
	buttonList.push_back(exitButton);
}

void MainMenu::onUpdate()
{

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

void MainMenu::createGame(Game::GameMode mode)
{
	Scene *scene = new Game(renderer, mode);
	SceneManager::loadScene(*scene);
}

void MainMenu::onClickNewGame()
{
	createGame(Game::SINGLE_PLAYER);
}

void MainMenu::onClickExit()
{
	SceneManager::quitGame();
}

void MainMenu::onClickTwoPlayers()
{
	createGame(Game::TWO_PLAYERS);
}