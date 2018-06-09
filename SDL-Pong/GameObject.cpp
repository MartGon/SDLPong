#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::updatePosition()
{
	texture.render(xPos, yPos);
}