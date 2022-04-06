#include "Player.h"

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::White);
	this->shape.setRadius(25.f);
	this->shape.setPosition(sf::Vector2f(600.f, 360.f));

	this->movementSpeed = 10.f;
}

Player::Player()
{
	this->initShape();
}

Player::~Player()
{

}

void Player::updateInput()
{
	// Move the player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::windowCollision(const sf::RenderTarget* target)
{
	// Check collision
	// Left side
	if (this->shape.getPosition().x <= 0.f)
	{
		this->shape.setPosition(0.f, this->shape.getPosition().y);
	}
	// Right side
	if (this->shape.getPosition().x >= target->getSize().x - this->shape.getRadius() * 2)
	{
		this->shape.setPosition(target->getSize().x - this->shape.getRadius() * 2, this->shape.getPosition().y);
	}
	// Top side
	if (this->shape.getPosition().y <= 0.f)
	{
		this->shape.setPosition(this->shape.getPosition().x, 0.f);
	}
	// Bottom side
	if (this->shape.getPosition().y >= target->getSize().y - this->shape.getRadius() * 2)
	{
		this->shape.setPosition(this->shape.getPosition().x, target->getSize().y - this->shape.getRadius() * 2);
	}
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();
	this->windowCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
