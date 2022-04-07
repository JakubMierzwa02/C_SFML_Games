#pragma once

#include "libs.h"
#include "Player.h"
#include "Bullet.h"

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
	Player* player;

	// Bullets
	Bullet bullet;
	std::vector<Bullet> bullets;

	// Vectors
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	// Private Functions
	void initVariables();
	void initWindow();
	void initPlayer();
	void initVectors();

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

