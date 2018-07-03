#include "ScoreBoard.h"

// Constructors

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::ScoreBoard(Texture texture) : GameObject(texture)
{

}

ScoreBoard::ScoreBoard(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	loadMedia();
}

ScoreBoard::~ScoreBoard()
{
}

// Methods

void ScoreBoard::initTexturePathVector()
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

void ScoreBoard::loadMedia()
{
	initTexturePathVector();

	for (auto const &path : texturePathVector)
	{
		textureVector.push_back(Texture(path, renderer));
	}
	texture = textureVector.front();
}

void ScoreBoard::setScore(int score)
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

	}
}