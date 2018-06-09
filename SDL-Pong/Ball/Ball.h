#include "../GameObject.h"
#include "../MainGame/Resources/Texture.h"
#include "../Player/Player.h"
#pragma once

class Ball : public GameObject
{
public:
	Ball();
	Ball(Texture texture);

	~Ball();

	// Players
	Player *player;
	Player *playerTwo;

	// Methods
	void move();
	bool checkCollisionWithPlayer(Player player);
};

