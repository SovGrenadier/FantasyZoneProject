#include "Bullet.h"


Bullet::Bullet(sf::Vector2f playPos, bool direction) : Weapons(playPos)
{
	velocity = sf::Vector2f(5.0f, 0.f);
	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{12,22},sf::Vector2i{8,16}});
}


Bullet::~Bullet()
{
}


void Bullet::death()
{
	//death logic
}

void Bullet::update(int input)
{

}