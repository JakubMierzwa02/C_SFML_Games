#pragma once

#include "libs.h"
#include "Player.h"
#include "Enemy.h"

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
	Player* player;

	// Bullets
	sf::CircleShape bullet;
	std::vector<sf::CircleShape> bullets;

	// Velocity of bullets
	sf::Vector2f currVelocity;
	std::vector<sf::Vector2f> currVelocities;
	float maxSpeed;

	int shootDelayMax;
	int shootDelay;

	// Enemies
	std::vector<Enemy*> enemies;
	float spawnTimerMax;
	float spawnTimer;

	// Vectors
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	// Private Functions
	void initVariables();
	void initWindow();
	void initPlayer();
	void initBullet();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	// Accessors

	// Modifiers

	// Functions
	void pollEvents();

	void updateVectors();
	void updateShooting();
	void updateEnemies();
	void updateCombat();
	void update();
	void render();

	void run();
};

