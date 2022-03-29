#include "Game.h"

void Game::initVariables()
{
	// Window
	this->windowWidth = 800;
	this->windowHeight = 600;
	this->videoMode = sf::VideoMode(this->windowWidth, this->windowHeight);
	this->name = "Game 1";

	// Game logic
	this->spawnTimerMax = 40;
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
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
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

void Game::spawnEnemy()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer++;
	else
	{
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

void Game::updateEnemies()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, this->movementSpeed);
	}
}

void Game::update()
{
	this->spawnEnemy();
	this->pollEvents();
	this->updateEnemies();
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
