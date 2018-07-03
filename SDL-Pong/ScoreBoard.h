#pragma once
#include "GameObject.h"
#include "Texture.h"
#include <vector>

class ScoreBoard : public GameObject
{
public:
	ScoreBoard();
	ScoreBoard(Texture texture);
	ScoreBoard(SDL_Renderer* renderer);
	~ScoreBoard();

	// String vector
	std::vector<const char*> texturePathVector;
	std::vector<Texture> textureVector;

	// Renderer
	SDL_Renderer *renderer;

	// Player's score
	int* playerScore;

	// Methods

	// Scoreboard
	void setScore(int score);

private:
	// Load textures
	void initTexturePathVector();
	void loadMedia();


};

