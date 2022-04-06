#pragma once

#include "libs.h"
#include "Player.h"

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

	// Player
	// HAVE TO ADD POINTER
	Player player;

	// Private Functions
	void initVariables();
	void initWindow();
	void initPlayer();

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

