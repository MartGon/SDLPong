#pragma once
#include "Texture.h"
#include "Vector2.h"
#include "GameObject.h"

class Counter : public GameObject
{
public:
	Counter();
	Counter(SDL_Renderer* renderer);
	~Counter();

	// Counter State
	enum CounterState
	{
		COUNTER_THREE,
		COUNTER_TWO,
		COUNTER_ONE,
		COUNTER_GO,
		COUNTER_FINISHED
	};

	CounterState state;

	// Renderer
	SDL_Renderer *renderer;

	// Texture for the animation
	Texture threeCounter;
	Texture twoCounter;
	Texture oneCounter;
	Texture goCounter;

	// Texture to render
	Texture toRender;

	// Position
	Vector2<float> pos;

	// Flag
	bool isPaused = true;

	// Methods
	void loadTextures();
	void setRelativePosition(Vector2<float> pos);
	void initCycle();
	void updateAlpha(Texture &texture, Uint8 step);
	void changeToNextState();
	bool hasAnimationFinished();

	// Upper Methods
	virtual void onUpdate();
	virtual void destroy();
};

