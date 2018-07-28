#include "Navigator.h"
#include "GameObject.h"

// Constructors

Navigator::Navigator()
{
	direction = Vector2();
	speed = 1;
}

Navigator::Navigator(Vector2 direction, int speed) : Component()
{
	this->direction = direction;
	this->speed = speed;
}

void Navigator::update()
{
	// Hook
	gameObject->beforeMove();

	Vector2 pos = gameObject->transform.position;
	Vector2 displacement = (direction * speed);
	Vector2 newPos = pos + displacement;
	gameObject->transform.position = newPos;

	// Hook
	gameObject->afterMove();
}

Vector2 Navigator::getDirection()
{
	return direction;
}

void Navigator::setDirection(Vector2 dir)
{
	dir.normalize();
	direction = dir;
}