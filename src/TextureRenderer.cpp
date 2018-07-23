#include "TextureRenderer.h"
#include "GameObject.h"

TextureRenderer::TextureRenderer() : Component()
{
	texture = Texture();
}

void TextureRenderer::update()
{
	int x = gameObject->transform.position.x;
	int y = gameObject->transform.position.y;

	texture.render(x, y);
}