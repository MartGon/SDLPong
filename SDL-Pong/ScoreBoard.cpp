#include "ScoreBoard.h"
#include "Utilities.h"
#include "MainGameLoop.h"


ScoreBoard::ScoreBoard()
{
}

ScoreBoard::ScoreBoard(SDL_Renderer* renderer, ScoreBoard::PlayerScoreBoard scoreboardType)
{
	// Set Object values
	this->renderer;
	this->scoreboardType = scoreboardType;

	// Create first display
	ScoreBoardNumberDisplay *displayOne = new ScoreBoardNumberDisplay(renderer);

	if (scoreboardType == PLAYER_ONE_SCOREBOARD)
		displayOne->xPos = WINDOW_WIDTH / 2 - 3 * displayOne->mColliderBox.w / 2;
	else
		displayOne->xPos = WINDOW_WIDTH / 2 + displayOne->mColliderBox.w / 2;
	
	displayOne->yPos = displayOne->texture.mHeight / 3;

	// Add to the list
	scoreBoardNumberDisplayVector.push_back(displayOne);
}

ScoreBoard::~ScoreBoard()
{
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

			int pXPos = previousDisplay->xPos;
			int pYPos = previousDisplay->yPos;

			if (scoreboardType == PLAYER_ONE_SCOREBOARD)
			{
				scoreDisplay->xPos = pXPos - (scoreDisplay->mColliderBox.w + scoreDisplay->mColliderBox.w / 4);
				scoreDisplay->yPos = pYPos;
			}
			else
			{
				// We put the new one where the front one used to be
				scoreDisplay->xPos = pXPos;
				scoreDisplay->yPos = pYPos;

				// We offset all the other ones
				
				for (auto display : scoreBoardNumberDisplayVector)
				{
					display->xPos += (display->mColliderBox.w + display->mColliderBox.w / 4);
				}
				
				//previousDisplay->xPos = pXPos + (scoreDisplay->texture.mWidth + scoreDisplay->texture.mWidth / 4);
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

void ScoreBoard::update()
{
	for (auto display : scoreBoardNumberDisplayVector)
	{
		display->updatePosition();
	}
}