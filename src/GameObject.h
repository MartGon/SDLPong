#pragma once
#include "Texture.h"
#include "Vector2.h"
#include "Transform.h"
#include "Collider.h"
#include <vector>

class Component;
class GameObject : public Updateable
{
public:
	GameObject();
	GameObject(Texture texture);
	~GameObject();

	// Active
	bool isActive = true;

	// Transform
	Transform transform;

	// Movement
	int speed = 5;

	// Methods

	// Init
	void start();
	virtual void onStart();

	// setComponent
	void setComponent(Component *component);

	// getComponent
	template <typename T>
	T* getComponent()
	{
		for (auto component : components)
		{
			if (T* subComponent = dynamic_cast<T*>(component))
			{
				return subComponent;
			}
		}

		return nullptr;
	}

	// Position
	void setRelativePosition(Vector2 pos);

	// Update
	virtual void onUpdate();
	void update() override;

	// Collisions
	virtual void onColliderEnter(Collider *collider);

	// Debug
	void drawCollisionBoundaries(SDL_Renderer *renderer);

	// Scale 
	void setScale(Vector2 scale);

	// Cleaning
	virtual void destroy();

private:

	// Components
	std::vector<Component*> components;

	// Bool
	bool isInitialized = false;
};

