#pragma once
#include "Texture.h"
#include "Vector2.h"
#include <vector>

class WinAlert
{
public:
	WinAlert();
	WinAlert(SDL_Renderer* renderer);
	~WinAlert();

	// Messages to display
	Texture playerMessage;
	Texture playerNumberMessage;
	Texture winsMessage;

	// Vector with player texture numbers
	std::vector<Texture*> playerNumbers;

	// Current position of the whole message
	Vector2 position;

	// Methods
	void loadPlayerNumbersTextures(SDL_Renderer* renderer);
	void setPlayerNumber(int number);
	void update();
	void setRelativePosition(Vector2 vector);
};

