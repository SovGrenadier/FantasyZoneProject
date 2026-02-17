#include "Bomb.h"


Bomb::Bomb(sf::Vector2f playerPos) : Weapons(playerPos)	
{
	velocity = sf::Vector2f(0.f, 5.f);
	damage = 5;
	//sprite->setTextureRect(sf::IntRect{ sf::Vector2i{70,35},sf::Vector2i{8,16} });
}


Bomb::~Bomb()
{
}


void Bomb::death()
{
	//death logic
}

void Bomb::update(int input)
{
	sprite->move({0, 1.5});
}