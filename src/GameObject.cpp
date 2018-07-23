#include "GameObject.h"
#include "SceneManager.h"
#include "TextureRenderer.h"

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

GameObject::GameObject(Texture texture) : GameObject()
{
	setComponent(new TextureRenderer(texture));
}

void GameObject::update()
{
	// Hook for initializing
	if (!isInitialized)
		start();

	// Update every component
	for (auto &component : components)
		if(component->isEnabled)
			component->update();

	// Hook for gameObject updates
	onUpdate();
}

/*
void GameObject::drawCollisionBoundaries(SDL_Renderer *renderer)
{
	SDL_Rect rect;
	rect.x = boundaries.left;
	rect.w = boundaries.right - boundaries.left;
	rect.y = boundaries.bottom;
	rect.h = boundaries.top - boundaries.bottom;
	SDL_RenderDrawRect(renderer, &rect);
}*/

void GameObject::setRelativePosition(Vector2 pos)
{

}

void GameObject::setScale(Vector2 scale)
{
	//texture.scale = scale;
}

void GameObject::start()
{
	onStart();

	isInitialized = true;
}

void GameObject::onStart()
{

}

void GameObject::onUpdate()
{

}

void GameObject::destroy()
{
	//texture.free();
	this->~GameObject();
}

void GameObject::setComponent(Component *component)
{
	component->gameObject = this;
	components.push_back(component);
}

void GameObject::onColliderEnter(Collider *collider)
{

}