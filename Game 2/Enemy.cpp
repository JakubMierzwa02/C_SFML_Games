#include "Enemy.h"

void Enemy::initShape()
{
	this->movementSpeed = 5.f;
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	this->shape.setPointCount(rand() % 7 + 1);
	this->shape.setRadius(40.f);
}

Enemy::Enemy(sf::Vector2f pos)
{
	this->initShape();
	this->shape.setPosition(pos);
}

Enemy::~Enemy()
{
	
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Enemy::update()
{
	this->shape.move(0.f, this->movementSpeed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
