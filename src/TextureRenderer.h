#pragma once
#include "Component.h"
#include "Texture.h"
#include <string>

class TextureRenderer : public Component
{
public:
	
	TextureRenderer();

	// Attributes
	Texture texture;
	std::string tPath;

	// methods
	void update() override;
};