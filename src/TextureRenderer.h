#pragma once
#include "Component.h"
#include "Texture.h"
#include <string>

class TextureRenderer : public Component
{
public:
	TextureRenderer();

	Texture texture;
	std::string path;
};