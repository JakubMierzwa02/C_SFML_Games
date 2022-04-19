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
	const sf::Vector2f getPosition() const;

	void update(sf::Vector2f);
	void render(sf::RenderTarget*);
};

