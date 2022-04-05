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

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{

	}
}

void Game::update()
{

}

void Game::render()
{
	this->window->clear();

	// Render stuff

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
