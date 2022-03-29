#include "Game.h"

void Game::initVariables()
{
	// Window
	this->windowWidth = 800;
	this->windowHeight = 600;
	this->videoMode = sf::VideoMode(this->windowWidth, this->windowHeight);
	this->name = "Game 1";

	// Game logic
	this->endGame = false;
	this->hp = 10;
	this->spawnTimerMax = 10;
	this->spawnTimer = this->spawnTimerMax;
	this->movementSpeed = 10.f;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, this->name, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	this->enemy.setFillColor(sf::Color::Green);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemy();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::run() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnEnemy()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer++;
	else
	{
		// Set random position
		this->enemy.setPosition(rand() % int(this->window->getSize().x - this->enemy.getSize().x), -this->enemy.getSize().y);

		// Set random color
		this->enemy.setFillColor(sf::Color(rand()%255+200, rand()%255+200, rand()%255+200, 255));

		// Push enemy to the vector and reset the timer
		this->enemies.push_back(this->enemy);
		this->spawnTimer = 0;
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		// Move enemies
		this->enemies[i].move(0.f, this->movementSpeed);

		// Check if enemy crossed bottom line
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}

		// Check if hovered over the enemy
		if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
		{
			this->enemies.erase(this->enemies.begin() + i);

			// Lose HP
			hp--;
			std::cout << "Health: " << this->hp << '\n';
		}
	}
}

void Game::update()
{
	if (hp < 1)
		this->endGame = true;
	if (!this->endGame)
	{
		this->spawnEnemy();
		this->pollEvents();
		this->updateMousePosition();
		this->updateEnemies();
	}
}

void Game::renderEnemies()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->window->draw(this->enemies[i]);
	}
}

void Game::render()
{
	this->window->clear();

	// Render stuff
	this->renderEnemies();

	this->window->display();
}
