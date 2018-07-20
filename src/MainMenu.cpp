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
	background->position.x = 0;
	background->position.y = 0;

	// Load title
	const char* titlePath = "PongTitle.png";
	gameTitle = Texture(titlePath, renderer);
	GameObject *title = new GameObject(gameTitle);
	title->position.x = WINDOW_WIDTH / 2 - gameTitle.mWidth / 2;
	title->position.y = WINDOW_HEIGHT / 64;

	
	// Load  newGame button
	const char* buttonPath = "NewGameButton.png";
	Texture newGameButtonTexture = Texture(buttonPath, renderer);
	newGameButton = new Button(newGameButtonTexture);
	newGameButton->position.x = WINDOW_WIDTH / 2 - newGameButton->texture.mWidth / 2;
	newGameButton->position.y = WINDOW_HEIGHT / 3;

	newGameButton->setOnClickListener(std::bind(&MainMenu::onClickNewGame, this));

	// Load  exitGame button
	const char* exitPath = "ExitButton.png";
	Texture exitGameButtonTexture = Texture(exitPath, renderer);
	exitButton = new Button(exitGameButtonTexture);
	exitButton->position.x = WINDOW_WIDTH / 2 - exitButton->texture.mWidth / 2;
	exitButton->position.y = WINDOW_HEIGHT / 1.2f;

	exitButton->setOnClickListener(std::bind(&MainMenu::onClickExit, this));

	// Load TwoPlayers Button
	const char* twoPlayersPath = "TwoPlayers.png";
	Texture twoPlayersButtonTexture = Texture(twoPlayersPath, renderer);
	twoPlayersButton = new Button(twoPlayersButtonTexture);
	twoPlayersButton->position.x = WINDOW_WIDTH / 2 - twoPlayersButton->texture.mWidth / 2;
	twoPlayersButton->position.y = WINDOW_HEIGHT / 2;

	twoPlayersButton->setOnClickListener(std::bind(&MainMenu::onClickTwoPlayers, this));

	// Load Online Button
	const char* onlineButtonPath = "OnlineButton.png";
	Texture onlineButtonTexture = Texture(onlineButtonPath, renderer);
	onlineButton = new Button(onlineButtonTexture);
	onlineButton->position.x = WINDOW_WIDTH / 2 - onlineButton->texture.mWidth / 2;
	onlineButton->position.y = WINDOW_HEIGHT / 1.5f;

	onlineButton->setOnClickListener(std::bind(&MainMenu::onClickOnline, this));

	// Load server Button
	const char* serverButtonPath = "ServerButton.png";
	Texture serverButtonTexture = Texture(serverButtonPath, renderer);
	serverButton = new Button(serverButtonTexture);
	serverButton->position.x = WINDOW_WIDTH / 2 - serverButton->texture.mWidth / 2;
	serverButton->position.y = WINDOW_HEIGHT / 3;
	serverButton->layer = 1;
	serverButton->isActive = false;

	serverButton->setOnClickListener(std::bind(&MainMenu::onClickServer, this));

	// Load client Button
	const char* clientButtonPath = "ClientButton.png";
	Texture clientButtonTexture = Texture(clientButtonPath, renderer);
	clientButton = new Button(clientButtonTexture);
	clientButton->position.x = WINDOW_WIDTH / 2 - clientButton->texture.mWidth / 2;
	clientButton->position.y = WINDOW_HEIGHT / 2;
	clientButton->layer = 1;
	clientButton->isActive = false;

	clientButton->setOnClickListener(std::bind(&MainMenu::onClickClient, this));

	// Load back button
	const char* backButtonPath = "BackButton.png";
	Texture backButtonTexture = Texture(backButtonPath, renderer);
	backButton = new Button(backButtonTexture);
	backButton->position.x = WINDOW_WIDTH / 2 - backButton->texture.mWidth / 2;
	backButton->position.y = WINDOW_HEIGHT / 1.5f;
	backButton->layer = 1;
	backButton->isActive = false;

	backButton->setOnClickListener(std::bind(&MainMenu::onClickBack, this));

	// Add them to the list
	buttonList.push_back(newGameButton);
	buttonList.push_back(twoPlayersButton);
	buttonList.push_back(exitButton);
	buttonList.push_back(onlineButton);

	// Layer 2
	buttonList.push_back(serverButton);
	buttonList.push_back(clientButton);
	buttonList.push_back(backButton);
}

void MainMenu::onUpdate()
{

}

void MainMenu::activateButtonLayer(Uint8 layer)
{
	for (auto const &button : buttonList)
	{
		if (button->layer == layer)
			button->isActive = true;
		else
			button->isActive = false;
	}
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
		if (!button->isActive)
			continue;

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

void MainMenu::onClickOnline()
{
	activateButtonLayer(1);
}

void MainMenu::onClickServer()
{
	printf("You have chosen server Mode\n");
	createGame(Game::ONLINE_SERVER);
}

void MainMenu::onClickClient()
{
	printf("You have chosen client Mode\n");
	createGame(Game::ONLINE_CLIENT);
}

void MainMenu::onClickBack()
{
	activateButtonLayer(0);
}