#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(float radius = 5.f)
	: currVelocity(0.f, 0.f), maxSpeed(15.f)
{
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setRadius(radius);
}

Bullet::~Bullet()
{

}

void Bullet::update()
{

}

void Bullet::render()
{

}
