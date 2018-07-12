#include "WinAlert.h"

WinAlert::WinAlert()
{
}

WinAlert::WinAlert(SDL_Renderer* renderer)
{
	// Load playerMessage Texture
	const char* pMPath = "PlayerWinsMessage.png";
	playerMessage = Texture(pMPath, renderer);

	// Load Wins Message Texture
	const char* wMPath = "WinsMessage.png";
	winsMessage = Texture(wMPath, renderer);

	// Load player Numbers
	loadPlayerNumbersTextures(renderer);

	// Load prompt to exit
	const char* prMPath = "PromptMessage.png";
	promptMessage = Texture(prMPath, renderer);
	decrementing = true;

	// Load prompt to rematch
	const char* rPrMpath = "PromptMessageRematch.png";
	rematchPromptMessage = Texture(rPrMpath, renderer);

	// Set Flags
	colliderEnabled = false;
	renderEnabled = false;
}

WinAlert::~WinAlert()
{
}

void WinAlert::loadPlayerNumbersTextures(SDL_Renderer* renderer)
{
	std::vector<const char*> paths;
	paths.push_back("PlayerOneMessage.png");
	paths.push_back("PlayerTwoMessage.png");

	for (auto const &path : paths)
	{
		Texture *texture = new Texture(path, renderer);
		playerNumbers.push_back(texture);
	}
}

void WinAlert::setPlayerNumber(int number)
{
	if (number >= playerNumbers.size())
		printf("Win Alert: Player Number higher than vector\n");
	else if (number < 0)
		printf("Win Alert: Player Number lower than zero\n");
	else
		playerNumberMessage = *playerNumbers.at(number);
}

void WinAlert::onUpdate()
{
	playerMessage.render(xPos, yPos);
	winsMessage.render(xPos, yPos + winsMessage.mHeight);
	playerNumberMessage.render(xPos, yPos);
	updatePrompt();
}

void WinAlert::setRelativePosition(Vector2 position)
{
	xPos = position.x - playerMessage.mWidth / 2;
	yPos = position.y - playerMessage.mHeight - winsMessage.mHeight;
}

void WinAlert::updatePrompt()
{
	promptMessage.render(xPos, yPos + winsMessage.mHeight + promptMessage.mHeight * 2);
	rematchPromptMessage.render(xPos, yPos + winsMessage.mHeight + promptMessage.mHeight * 3);
	updateAlpha(promptMessage, 3);
	updateAlpha(rematchPromptMessage, 3);
}

void WinAlert::updateAlpha(Texture &texture, Uint8 step)
{
	Uint8 alpha = texture.getAlpha();

	if (decrementing)
	{
		if (alpha - step >= 0)
			alpha -= step;
		else
		{
			decrementing = false;
			alpha = 0;
		}
	}
	else
	{
		if (alpha + step <= 255 )
			alpha += step;
		else
		{
			decrementing = true;
			alpha = 255;
		}
	}

	texture.setAlpha(alpha);
}