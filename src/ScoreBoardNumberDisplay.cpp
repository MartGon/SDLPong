#include "ScoreBoardNumberDisplay.h"

std::vector<const char*> ScoreBoardNumberDisplay::texturePathVector;
std::vector<Texture> ScoreBoardNumberDisplay::textureVector;

// Constructors

ScoreBoardNumberDisplay::ScoreBoardNumberDisplay()
{
}

ScoreBoardNumberDisplay::ScoreBoardNumberDisplay(Texture texture) : GameObject(texture)
{

}

ScoreBoardNumberDisplay::ScoreBoardNumberDisplay(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	tRenderer = new TextureRenderer();
	setComponent(tRenderer);

	loadMedia();

	collider = new Collider(tRenderer->texture);
	setComponent(collider);
	setScale(Vector2<float>(0.5f, 0.5f));
}

ScoreBoardNumberDisplay::~ScoreBoardNumberDisplay()
{
}

// Methods

void ScoreBoardNumberDisplay::initTexturePathVector()
{
	texturePathVector.push_back("ZeroScoreBoard.png");

	texturePathVector.push_back("OneScoreBoard.png");
	texturePathVector.push_back("TwoScoreBoard.png");
	texturePathVector.push_back("ThreeScoreBoard.png");

	texturePathVector.push_back("FourScoreBoard.png");
	texturePathVector.push_back("FiveScoreBoard.png");
	texturePathVector.push_back("SixScoreBoard.png");

	texturePathVector.push_back("SevenScoreBoard.png");
	texturePathVector.push_back("EightScoreBoard.png");
	texturePathVector.push_back("NineScoreBoard.png");
}

void ScoreBoardNumberDisplay::loadMedia()
{
	if (textureVector.empty())
	{
		initTexturePathVector();

		for (auto const &path : texturePathVector)
		{
			Texture texture(path, renderer);
			textureVector.push_back(texture);
		}
	}
	tRenderer->texture = textureVector.front();
}

void ScoreBoardNumberDisplay::setNumber(int score)
{
	if (score < 0)
	{
		printf("Can't set negative score value\n");
		return;
	}
	if (score < textureVector.size())
	{
		//printf("Setting score to %i\n", score);
		tRenderer->texture = textureVector.at(score);
	}
	else
	{
		printf("Can't set a score value bigger than 9\n");
	}
}

void ScoreBoardNumberDisplay::destroy()
{
	GameObject::destroy();

	for (auto &texture : textureVector)
		texture.free();

	textureVector.clear();
}

void ScoreBoardNumberDisplay::onStart()
{
	tRenderer = getComponent<TextureRenderer>();
	collider = getComponent<Collider>();
}