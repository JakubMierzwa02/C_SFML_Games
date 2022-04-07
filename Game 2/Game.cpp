#include "Game.h"

void Game::initVariables()
{
	this->windowName = "Game 2";
	this->windowWidth = 1280;
	this->windowHeight = 720;
	this->videoMode = sf::VideoMode(this->windowWidth, this->windowHeight);
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(videoMode, windowName, sf::Style::Resize | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player;
}

void Game::initVectors()
{
	this->playerCenter = sf::Vector2f(this->player->getPlayer().getPosition().x + player->getPlayer().getRadius(), this->player->getPlayer().getPosition().y + this->player->getPlayer().getRadius());
	this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
	this->aimDir = this->mousePosWindow - this->playerCenter;
	this->aimDirNorm = sf::Vector2f(this->aimDir.x / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)), this->aimDir.y / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)));
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initVectors();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->pollEvents();

	// Update the player
	this->player->update(this->window);
}

void Game::render()
{
	this->window->clear();

	// Render stuff
	this->player->render(this->window);

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
