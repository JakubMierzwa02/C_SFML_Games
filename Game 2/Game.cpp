#include "Game.h"

void Game::initVariables()
{
	// Window
	this->windowName = "Game 2";
	this->windowWidth = 1280;
	this->windowHeight = 720;
	this->videoMode = sf::VideoMode(this->windowWidth, this->windowHeight);

	// Game logic
	this->points = 0;
	this->healthMax = 10;
	this->health = this->healthMax;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(videoMode, windowName, sf::Style::Resize | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initGui()
{
	if (!this->font.loadFromFile("Fonts/font.ttf"))
		throw "Error: Could not open font.ttf file";

	this->guiText.setFont(this->font);
	this->guiText.setCharacterSize(32);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setString("NONE");
}

void Game::initPlayer()
{
	this->player = new Player;
}

void Game::initBullet()
{
	this->bullet.setFillColor(sf::Color::Red);
	this->bullet.setRadius(5.f);
	this->maxSpeed = 20.f;
	this->currVelocity.x = 0.f;
	this->currVelocity.y = 0.f;
}

void Game::initEnemies()
{
	this->spawnTimerMax = 10.f;
	this->spawnTimer = 0.f;

	this->currEnemyVelocity.x = 0.f;
	this->currEnemyVelocity.y = 0.f;
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initGui();
	this->initPlayer();
	this->initBullet();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	for (auto enemy : this->enemies)
	{
		delete enemy;
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateVectors()
{
	// Bullets
	this->playerCenter = sf::Vector2f(this->player->getPlayer().getPosition().x + player->getPlayer().getRadius(), this->player->getPlayer().getPosition().y + this->player->getPlayer().getRadius());
	this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
	this->aimDir = this->mousePosWindow - this->playerCenter;
	this->aimDirNorm = sf::Vector2f(this->aimDir.x / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)), this->aimDir.y / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)));
}

void Game::updateInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullet.setPosition(this->playerCenter);
		this->currVelocity = this->aimDirNorm * this->maxSpeed;

		this->currVelocities.push_back(this->currVelocity);
		this->bullets.push_back(this->bullet);
	}
}

void Game::updateShooting()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		// Move bullets
		this->bullets[i].move(this->currVelocities[i]);

		// Out of bounds collision
		if (this->bullets[i].getPosition().x + this->bullets[i].getRadius() * 2 < 0
			|| this->bullets[i].getPosition().x > this->window->getSize().x
			|| this->bullets[i].getPosition().y + this->bullets[i].getRadius() * 2 < 0
			|| this->bullets[i].getPosition().y > this->window->getSize().y)
		{
			this->bullets.erase(this->bullets.begin() + i);
			this->currVelocities.erase(this->currVelocities.begin() + i);
		}
	}
}

void Game::updateEnemies()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		int randPos = rand() % this->window->getSize().x;
		this->enemies.push_back(new Enemy(sf::Vector2f(randPos, -50.f)));
		this->enemySpawnPoint = sf::Vector2f(randPos, -50.f);
		this->enemySpawnPoints.push_back(this->enemySpawnPoint);
		this->targetPoint = sf::Vector2f(rand() % this->window->getSize().x, this->window->getSize().y + 100.f);
		this->targetPoints.push_back(this->targetPoint);

		this->enemyDir = this->targetPoint - this->enemySpawnPoint;
		this->enemyDirs.push_back(this->enemyDir);
		this->enemyDirNorm = sf::Vector2f(this->enemyDir.x / sqrt(pow(this->enemyDir.x, 2) + pow(this->enemyDir.y, 2)), this->enemyDir.y / sqrt(pow(this->enemyDir.x, 2) + pow(this->enemyDir.y, 2)));
		this->enemyDirNorms.push_back(this->enemyDirNorm);

		this->currEnemyVelocity = this->enemyDirNorm * 8.f;
		this->currEnemyVelocities.push_back(this->currEnemyVelocity);

		this->spawnTimer = 0.f;
	}

	// Check if enemy is out of window
	for (size_t i = 0; i < this->enemies.size(); i++)
	{	
		this->enemies[i]->update(this->currEnemyVelocities[i]);

		if (this->enemies[i]->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			this->enemySpawnPoints.erase(this->enemySpawnPoints.begin() + i);
			this->targetPoints.erase(this->targetPoints.begin() + i);
			this->enemyDirs.erase(this->enemyDirs.begin() + i);
			this->enemyDirNorms.erase(this->enemyDirNorms.begin() + i);
			this->currEnemyVelocities.erase(this->currEnemyVelocities.begin() + i);
		}
	}
}

void Game::updateCombat()
{
	// Check if bullet or player hits enemy
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		bool erased = false;
		for (size_t k = 0; k < this->bullets.size() && !erased; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k].getGlobalBounds()))
			{
				// Gain points
				this->points++;

				// Delete enemy and bullet
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				this->enemySpawnPoints.erase(this->enemySpawnPoints.begin() + i);
				this->targetPoints.erase(this->targetPoints.begin() + i);
				this->enemyDirs.erase(this->enemyDirs.begin() + i);
				this->enemyDirNorms.erase(this->enemyDirNorms.begin() + i);
				this->currEnemyVelocities.erase(this->currEnemyVelocities.begin() + i);

				this->bullets.erase(this->bullets.begin() + k);
				this->currVelocities.erase(this->currVelocities.begin() + k);
				erased = true;
			}
		}

		if (this->enemies[i]->getBounds().intersects(this->player->getPlayer().getGlobalBounds()))
		{
			// Lose health
			this->health--;

			// Delete enemy
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			this->enemySpawnPoints.erase(this->enemySpawnPoints.begin() + i);
			this->targetPoints.erase(this->targetPoints.begin() + i);
			this->enemyDirs.erase(this->enemyDirs.begin() + i);
			this->enemyDirNorms.erase(this->enemyDirNorms.begin() + i);
			this->currEnemyVelocities.erase(this->currEnemyVelocities.begin() + i);

			erased = true;
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "Points: " << this->points << '\n' << "Health: " << this->health << '\n';

	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	// Update the player
	this->player->update(this->window);

	this->updateVectors();
	this->updateInput();

	// Update shooting
	this->updateShooting();

	this->updateEnemies();
	this->updateCombat();
	this->updateGui();
}

void Game::render()
{
	this->window->clear();

	// Render stuff
	this->player->render(this->window);

	// Render bullets
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->window->draw(this->bullets[i]);
	}

	// Render enemies
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->render(this->window);
	}

	// Render GUI
	this->window->draw(this->guiText);

	this->window->display();
}

void Game::run()
{
	// Game loop
	while (this->window->isOpen() && this->health > 0)
	{
		this->update();
		this->render();
	}
}
