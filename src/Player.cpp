#include "Player.h"

// Constructors

Player::Player()
{

}

Player::Player(Texture texture) : GameObject(texture)
{
	score = 0;
	collider = new Collider(texture);
	setComponent(collider);
}

Player::~Player()
{

}

// Methods

void Player::onStart()
{
	collider = getComponent<Collider>();
}

void Player::move(Player::MoveDirection direction) 
{
	if (direction == Player::MoveDirection::MOVE_UP)
	{
		if(transform.position.y > 0)
			transform.position.y -= speed;
	}
	else
	{
		if(transform.position.y < 480 - collider->getDimensions().y)
			transform.position.y += speed;
	}
}

void Player::addPoint(Uint8 point)
{
	score += point;
	if(scoreBoard)
		scoreBoard->setScore(score);
}

void Player::resetScore()
{
	score = 0;
	if(scoreBoard)
		scoreBoard->setScore(score);
}