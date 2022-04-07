#pragma once

#include "libs.h"

class Bullet
{
private:
	sf::CircleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;

public:
	Bullet();
	Bullet(float radius);
	virtual ~Bullet();

	// Accessors
	sf::CircleShape getShape();

	void update();
	void render();
};

