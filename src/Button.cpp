#include "Button.h"


// Constructors

Button::Button()
{
}

Button::Button(Texture texture) : GameObject(texture)
{

}

Button::~Button()
{
}

// Methods

void Button::handleEvent(SDL_Event *e)
{
	switch (e->type)
	{
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		default:
			break;
	}

}

const bool Button::isWithinBoundaries(int mousePosX, int mousePosY)
{
	bool inside = false;

	int x = mousePosX;
	int y = mousePosY;

	if (x < boundaries.left)
		return false;
	else if (x > boundaries.right)
		return false;
	else if (y < boundaries.top)
		return false;
	else if (y > boundaries.bottom)
		return false;
	else
		return true;
}

void Button::setOnClickListener(std::function<void()> callback)
{
	onClick = callback;
}