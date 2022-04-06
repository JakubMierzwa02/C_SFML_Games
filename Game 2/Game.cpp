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
	//this->player = new Player;
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
	//delete this->player;
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
	this->player.update(this->window);
}

void Game::render()
{
	this->window->clear();

	// Render stuff
	this->player.render(this->window);

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
