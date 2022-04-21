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

	// Game logic
	unsigned points;
	int healthMax;
	int health;
	
	// Resources
	sf::Texture backgroundTex;
	sf::Font font;

	// GUI
	sf::Text guiText;

	// Player
	Player* player;

	// Bullets
	sf::CircleShape bullet;
	std::vector<sf::CircleShape> bullets;

	// Velocity of bullets
	sf::Vector2f currVelocity;
	std::vector<sf::Vector2f> currVelocities;
	float maxSpeed;

	// Enemies
	std::vector<Enemy*> enemies;
	float spawnTimerMax;
	float spawnTimer;
	bool erased;

	// Velocity of Enemies
	sf::Vector2f currEnemyVelocity;
	std::vector<sf::Vector2f> currEnemyVelocities;

	// Vectors
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	sf::Vector2f enemySpawnPoint;
	std::vector<sf::Vector2f> enemySpawnPoints;
	sf::Vector2f targetPoint;
	std::vector<sf::Vector2f> targetPoints;
	sf::Vector2f enemyDir;
	std::vector<sf::Vector2f> enemyDirs;
	sf::Vector2f enemyDirNorm;
	std::vector<sf::Vector2f> enemyDirNorms;

	// Private Functions
	void initVariables();
	void initWindow();
	void initGui();
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
	void updateInput();
	void updateShooting();
	void updateEnemies();
	void updateCombat();
	void updateGui();
	void update();
	void render();

	void run();
};

