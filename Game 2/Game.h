#pragma once

#include "libs.h"

class Game
{
private:
	sf::RenderWindow* window;
	std::string windowName;
	int windowWidth;
	int windowHeight;
	sf::VideoMode videoMode;

	// Events
	sf::Event event;

	// Private Functions
	void initVariables();
	void initWindow();

public:
	Game();
	virtual ~Game();

	// Accessors

	// Modifiers

	// Functions
	void pollEvents();

	void update();
	void render();

	void run();
};

