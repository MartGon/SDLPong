#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::updatePosition()
{
	computeBoundaries();
	texture.render(xPos, yPos);
}

void GameObject::computeBoundaries()
{
	boundaries.left = xPos + (texture.mWidth - mColliderBox.w) / 2;
	boundaries.right = xPos + mColliderBox.w + (texture.mWidth - mColliderBox.w) / 2;
	boundaries.top = yPos + (texture.mHeight - mColliderBox.h) / 2;
	boundaries.bottom = yPos + mColliderBox.h + (texture.mHeight - mColliderBox.h) / 2;
}