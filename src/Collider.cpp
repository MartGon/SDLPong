#include "Collider.h"
#include "GameObject.h"

// Attributes
std::vector<Collider*> Collider::gColliders = std::vector<Collider*>();

Collider::Collider() : Component()
{

}

Collider::Collider(int width, int height) : Component()
{
	// Set values
	cWidth = width;
	cHeight = height;

	// Calculate box
	calculateColliderBox();

	// Add to static list
	gColliders.push_back(this);
}

void Collider::calculateColliderBox()
{
	cWidth = cWidth * gameObject->transform.scale.x;
	cHeight = cHeight * gameObject->transform.scale.y;
}

void Collider::calculateColliderBoundaries()
{
	Vector2 position = gameObject->transform.position;

	cLeft = position.x + offset.x;
	cRight = position.x + cWidth + offset.x;
	cTop = position.y + offset.y;
	cBottom = position.y + cHeight;
}

Vector2 Collider::getCollisionCenter()
{
	int x = (float)(cLeft + cRight) / 2;
	int y = (float)(cTop + cBottom) / 2;

	return Vector2(x, y);
}

void Collider::update()
{
	calculateColliderBoundaries();

	for (auto const& collider : gColliders)
		if (this == collider)
			continue;
		else if (isCollidingWith(collider))
			gameObject->onColliderEnter(collider);
}

bool Collider::isCollidingWith(Collider *collider)
{
	if (cRight <= collider->cLeft)
		return false;

	if (cLeft >= collider->cRight)
		return false;

	if (cBottom <= collider->cTop)
		return false;

	if (cTop >= collider->cBottom)
		return false;

	return true;
}