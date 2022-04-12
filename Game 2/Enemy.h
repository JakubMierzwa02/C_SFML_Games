#pragma once

#include "libs.h"

class Enemy
{
private:
	sf::RectangleShape shape;
	float movementSpeed;

	void initShape();

public:
	Enemy();
	virtual ~Enemy();

	void update();
	void render();
};

