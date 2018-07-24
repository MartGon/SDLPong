#include "ScoreBoard.h"
#include "Utilities.h"
#include "MainGameLoop.h"


ScoreBoard::ScoreBoard()
{
}

ScoreBoard::ScoreBoard(SDL_Renderer* renderer, ScoreBoard::PlayerScoreBoard scoreboardType) : GameObject()
{
	// Set Object values
	this->renderer = renderer;
	this->scoreboardType = scoreboardType;
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::onStart()
{
	// Create first display
	ScoreBoardNumberDisplay *displayOne = new ScoreBoardNumberDisplay(renderer);

	if (scoreboardType == PLAYER_ONE_SCOREBOARD)
		displayOne->transform.position.x = WINDOW_WIDTH / 2 - 3 * displayOne->collider->getDimensions().x/ 2;
	else
		displayOne->transform.position.x = WINDOW_WIDTH / 2 + displayOne->collider->getDimensions().x / 2;

	displayOne->transform.position.y = WINDOW_HEIGHT / 16;

	// Add to the list
	scoreBoardNumberDisplayVector.push_back(displayOne);
}

void ScoreBoard::setScore(int score)
{
	int displaysRequired = Utilities::getNumberOfDigits(score);

	int nDisplayToCreate = displaysRequired - scoreBoardNumberDisplayVector.size();
	
	// It's necessary to create more displays
	if (nDisplayToCreate > 0)
	{
		for (int i = 0; i < nDisplayToCreate; i++)
		{
			ScoreBoardNumberDisplay *scoreDisplay = new ScoreBoardNumberDisplay(renderer);
			ScoreBoardNumberDisplay *previousDisplay = scoreBoardNumberDisplayVector.back();

			int xPos = previousDisplay->transform.position.x;
			int yPos = previousDisplay->transform.position.y;

			if (scoreboardType == PLAYER_ONE_SCOREBOARD)
			{
				scoreDisplay->transform.position.x = xPos - (scoreDisplay->collider->getDimensions().x + scoreDisplay->collider->getDimensions().x / 4);
				scoreDisplay->transform.position.y = yPos;
			}
			else
			{
				// We put the new one where the front one used to be
				scoreDisplay->transform.position.x = xPos;
				scoreDisplay->transform.position.y = yPos;

				// We offset all the other ones
				
				for (auto display : scoreBoardNumberDisplayVector)
				{
					display->transform.position.x += (display->collider->getDimensions().x + display->collider->getDimensions().x / 4);
				}
				
				//previousDisplay->position.x = xPos + (scoreDisplay->texture.mWidth + scoreDisplay->texture.mWidth / 4);
			}
			scoreBoardNumberDisplayVector.push_back(scoreDisplay);
		}
	}

	std::vector<int> digits = Utilities::getDigitsFromNumber(score);
	for (int i = 0; i < digits.size(); i++)
	{
		ScoreBoardNumberDisplay *displayToModify = scoreBoardNumberDisplayVector.at(i);
		displayToModify->setNumber(digits.at(i));
	}
}

void ScoreBoard::onUpdate()
{
	for (auto display : scoreBoardNumberDisplayVector)
	{
		display->update();
	}
}

void ScoreBoard::destroy()
{
	//GameObject::destroy();

	for (auto &display : scoreBoardNumberDisplayVector)
		display->destroy();
}