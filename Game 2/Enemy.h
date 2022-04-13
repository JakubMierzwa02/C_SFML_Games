#pragma once

#include "libs.h"

class Enemy
{
private:
	sf::CircleShape shape;
	float movementSpeed;

	void initShape();

public:
	Enemy(sf::Vector2f);
	virtual ~Enemy();

	// Accessors
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget*);
};

