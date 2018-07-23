#pragma once
#include "GameObject.h"
#include "TextureRenderer.h";
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

	// Attributes
	TextureRenderer *tRenderer = nullptr;

	// Colllider
	Collider *collider = nullptr;

	// Renderer
	SDL_Renderer *renderer;

	// Methods
	void onStart() override;

	// Scoreboard
	void setNumber(int score);
	virtual void destroy();

private:
	// Load textures
	void initTexturePathVector();
	void loadMedia();


};

