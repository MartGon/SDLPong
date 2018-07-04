#pragma once
#include "GameObject.h"
#include "Texture.h"
#include <vector>

class ScoreBoardNumberDisplay : public GameObject
{
public:
	ScoreBoardNumberDisplay();
	ScoreBoardNumberDisplay(Texture texture);
	ScoreBoardNumberDisplay(SDL_Renderer* renderer);
	~ScoreBoardNumberDisplay();

	// String vector
	static std::vector<const char*> texturePathVector;
	static std::vector<Texture> textureVector;

	// Renderer
	SDL_Renderer *renderer;

	// Methods

	// Scoreboard
	void setNumber(int score);

private:
	// Load textures
	void initTexturePathVector();
	void loadMedia();


};

