#include "ScoreBoard.h"
#include "Utilities.h"
#include "MainGameLoop.h"


ScoreBoard::ScoreBoard()
{
}

ScoreBoard::ScoreBoard(SDL_Renderer* renderer, ScoreBoard::PlayerScoreBoard scoreboardType) : GameObject()
{
	// Set Object values
	this->renderer;
	this->scoreboardType = scoreboardType;

	// Set flags
	renderEnabled = false;
	colliderEnabled = false;

	// Create first display
	ScoreBoardNumberDisplay *displayOne = new ScoreBoardNumberDisplay(renderer);

	if (scoreboardType == PLAYER_ONE_SCOREBOARD)
		displayOne->position.x = WINDOW_WIDTH / 2 - 3 * displayOne->mColliderBox.w / 2;
	else
		displayOne->position.x = WINDOW_WIDTH / 2 + displayOne->mColliderBox.w / 2;
	
	displayOne->position.y = displayOne->texture.mHeight / 3;

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

			int xPos = previousDisplay->position.x;
			int yPos = previousDisplay->position.y;

			if (scoreboardType == PLAYER_ONE_SCOREBOARD)
			{
				scoreDisplay->position.x = xPos - (scoreDisplay->mColliderBox.w + scoreDisplay->mColliderBox.w / 4);
				scoreDisplay->position.y = yPos;
			}
			else
			{
				// We put the new one where the front one used to be
				scoreDisplay->position.x = xPos;
				scoreDisplay->position.y = yPos;

				// We offset all the other ones
				
				for (auto display : scoreBoardNumberDisplayVector)
				{
					display->position.x += (display->mColliderBox.w + display->mColliderBox.w / 4);
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