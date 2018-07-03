#pragma once
#include "GameObject.h"
#include <functional>

class Button : public GameObject
{
public:
	// Constructors
	Button();
	Button(Texture texture);
	~Button();

	// Methods
	void handleEvent(SDL_Event* e);

	const bool isWithinBoundaries(int mousePosX, int mousePosY);

	// Listener
	std::function<void()> onClick;

	// set onClick
	void setOnClickListener(std::function<void()> callback);
};

