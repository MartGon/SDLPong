#include "Counter.h"

Counter::Counter()
{
}

Counter::Counter(SDL_Renderer *renderer) 
{
	this->renderer = renderer;
	loadTextures();
	initCycle();
}

Counter::~Counter()
{
}

// Methods

void Counter::loadTextures()
{
	const char* onePath = "1Counter.png";
	oneCounter = Texture(onePath, renderer);

	const char *twoPath = "2Counter.png";
	twoCounter = Texture(twoPath, renderer);

	const char *threePath = "3Counter.png";
	threeCounter = Texture(threePath, renderer);

	const char *goPath = "GoCounter.png";
	goCounter = Texture(goPath, renderer);
}

void Counter::setRelativePosition(Vector2 pos)
{
	this->pos.x = pos.x - oneCounter.mWidth;
	this->pos.y = pos.y - oneCounter.mHeight * 3;
}

void Counter::update()
{
	if (hasAnimationFinished())
		return;

	updateAlpha(toRender, 6);
	toRender.scale = Vector2(2, 2);
	toRender.render(pos.x, pos.y);
}

void Counter::initCycle()
{
	// Reset alpha values
	oneCounter.setAlpha(255);
	twoCounter.setAlpha(255);
	threeCounter.setAlpha(255);
	goCounter.setAlpha(255);

	toRender = threeCounter;
	state = COUNTER_THREE;
}

void Counter::updateAlpha(Texture &texture, Uint8 step)
{
	Uint8 alpha = texture.getAlpha();

	if (alpha >= step)
		alpha -= step;
	else
	{
		changeToNextState();
		return;
	}

	texture.setAlpha(alpha);
}

void Counter::changeToNextState()
{
	switch (state)
	{
	case Counter::COUNTER_THREE:
		toRender = twoCounter;
		state = COUNTER_TWO;
		break;
	case Counter::COUNTER_TWO:
		toRender = oneCounter;
		state = COUNTER_ONE;
		break;
	case Counter::COUNTER_ONE:
		toRender = goCounter;
		pos.x = pos.x + oneCounter.mWidth - goCounter.mWidth;
		state = COUNTER_GO;
		break;
	case Counter::COUNTER_GO:
		pos.x = pos.x + goCounter.mWidth - oneCounter.mWidth;
		state = COUNTER_FINISHED;
		break;
	default:
		break;
	}
}

bool Counter::hasAnimationFinished()
{
	return state == COUNTER_FINISHED;
}