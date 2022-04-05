#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	std::string name;
	int windowWidth;
	int windowHeight;

	// Events
	sf::Event ev;

	// Game logic
	bool endGame;
	int hp;
	int spawnTimer;
	int spawnTimerMax;
	float movementSpeed;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Enemy
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	// Resources
	sf::Font font;
	sf::Text text;

	// Functions
	void initVariables();
	void initWindow();
	void initFont();
	void initText();
	void initEnemy();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool run() const;
	const bool getEndGame() const;

	// Functions
	void spawnEnemy();
	void pollEvents();

	// Update
	void updateText();
	void updateMousePosition();
	void updateEnemies();
	void update();

	// Render
	void renderText();
	void renderEnemies();
	void render();
};

