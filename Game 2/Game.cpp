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

void Game::initBullet()
{
	this->bullet.setFillColor(sf::Color::Red);
	this->bullet.setRadius(5.f);
	this->maxSpeed = 15.f;
	this->currVelocity.x = 0.f;
	this->currVelocity.y = 0.f;

	this->shootDelayMax = 4.f;
	this->shootDelay = this->shootDelayMax;
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initBullet();
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

void Game::updateVectors()
{
	this->playerCenter = sf::Vector2f(this->player->getPlayer().getPosition().x + player->getPlayer().getRadius(), this->player->getPlayer().getPosition().y + this->player->getPlayer().getRadius());
	this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
	this->aimDir = this->mousePosWindow - this->playerCenter;
	this->aimDirNorm = sf::Vector2f(this->aimDir.x / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)), this->aimDir.y / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)));
}

void Game::updateShooting()
{
	if (this->shootDelay < this->shootDelayMax)
		this->shootDelay++;
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->bullet.setPosition(this->playerCenter);
			this->currVelocity = aimDirNorm * maxSpeed;

			this->currVelocities.push_back(this->currVelocity);
			this->bullets.push_back(this->bullet);
		}

		this->shootDelay = 0;
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		this->bullets[i].move(this->currVelocities[i]);
	}
}

void Game::update()
{
	this->pollEvents();

	// Update the player
	this->player->update(this->window);

	this->updateVectors();

	// Update shooting
	this->updateShooting();
}

void Game::render()
{
	this->window->clear();

	// Render stuff
	this->player->render(this->window);

	// Render bullets
	for (size_t i = 0; i < bullets.size(); i++)
	{
		this->window->draw(bullets[i]);
	}

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
