#pragma once
#include "Texture.h"
#include "Vector2.h"
#include "GameObject.h"
#include <vector>

class WinAlert : public GameObject
{
public:
	WinAlert();
	WinAlert(SDL_Renderer* renderer);
	~WinAlert();

	// Messages to display
	Texture playerMessage;
	Texture playerNumberMessage;
	Texture winsMessage;
	Texture promptMessage;
	Texture rematchPromptMessage;

	// Vector with player texture numbers
	std::vector<Texture*> playerNumbers;

	// Methods
	void loadPlayerNumbersTextures(SDL_Renderer* renderer);
	void setPlayerNumber(int number);
	void setRelativePosition(Vector2<float> vector);

	// Animating
	bool decrementing;
	void updatePrompt();
	void updateAlpha(Texture &texture, Uint8 step);

	// Upper methods
	void onUpdate();
	virtual void destroy();
};

