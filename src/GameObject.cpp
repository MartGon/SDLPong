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
	name = texture.path;
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

void GameObject::setRelativePosition(Vector2 pos)
{

}

void GameObject::setScale(Vector2 scale)
{
	transform.scale = scale;
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
	for (auto &component : components)
		component->destroy();

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