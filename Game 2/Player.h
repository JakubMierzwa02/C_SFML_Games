#pragma once

#include "libs.h"

class Player
{
private:
	sf::CircleShape shape;
	float movementSpeed;
	int attackCooldownMax;
	int attackCooldown;

	// Private functions
	void initShape();

public:
	Player();
	virtual ~Player();

	// Accessors
	const sf::CircleShape getPlayer() const;
	const bool canAttack();

	void updateInput();
	void windowCollision(const sf::RenderTarget*);

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

