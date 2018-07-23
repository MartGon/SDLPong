#include "GameObject.h"
#include "SceneManager.h"


GameObject::GameObject()
{
	// Add to the scene updater
	SceneManager::scene->addGameObject(this);

	// Add reference to self in transform component
	transform = Transform();
	transform.gameObject = this;
}

GameObject::~GameObject()
{
}

GameObject::GameObject(Texture texture)
{
	this->texture = texture;
	calculateColliderBox();

	SceneManager::scene->addGameObject(this);
}

void GameObject::update()
{
	// Calculate collision boundaries
	if(colliderEnabled)
		computeBoundaries();

	// Render default texture if enabled
	if(renderEnabled)
		texture.render(position.x, position.y);

	// Hook for gameObject updates
	onUpdate();
}

void GameObject::computeBoundaries()
{
	boundaries.left = position.x + (texture.mWidth * texture.scale.x - mColliderBox.w) / 2;
	boundaries.right = position.x + mColliderBox.w + (texture.mWidth * texture.scale.x - mColliderBox.w) / 2;
	boundaries.top = position.y + (texture.mHeight * texture.scale.y - mColliderBox.h) / 2;
	boundaries.bottom = position.y + mColliderBox.h + (texture.mHeight * texture.scale.y - mColliderBox.h) / 2;
}

Vector2 GameObject::getCollisionCenter()
{
	int x = (float)(boundaries.right - boundaries.left) / 2 + position.x + (texture.mWidth * texture.scale.x - mColliderBox.w) / 2;
	int y = (float)(boundaries.bottom - boundaries.top) / 2 + position.y + (texture.mHeight * texture.scale.y - mColliderBox.h) / 2;

	return Vector2(x, y);
}

void GameObject::drawCollisionBoundaries(SDL_Renderer *renderer)
{
	SDL_Rect rect;
	rect.x = boundaries.left;
	rect.w = boundaries.right - boundaries.left;
	rect.y = boundaries.bottom;
	rect.h = boundaries.top - boundaries.bottom;
	SDL_RenderDrawRect(renderer, &rect);
}

void GameObject::setScale(Vector2 scale)
{
	texture.scale = scale;

	calculateColliderBox();
}

void GameObject::calculateColliderBox()
{
	mColliderBox.w = texture.mWidth * texture.scale.x;
	mColliderBox.h = texture.mHeight * texture.scale.y;
}

void GameObject::onUpdate()
{

}

void GameObject::destroy()
{
	texture.free();
	this->~GameObject();
}

void GameObject::setRelativePosition(Vector2 pos)
{

}

void GameObject::setComponent(Component *component)
{
	component->gameObject = this;
	components.push_back(component);
}

void GameObject::onColliderEnter(Collider *collider)
{

}