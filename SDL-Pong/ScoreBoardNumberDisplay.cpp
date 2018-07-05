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
	loadMedia();
	calculateColliderBox();
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
			texture.scale = Vector2(0.5f, 0.5f);
			textureVector.push_back(texture);
		}
	}
	texture = textureVector.front();
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
		texture = textureVector.at(score);
	}
	else
	{
		printf("Can't set a score value bigger than 9\n");
	}
}