#include "Bomb.h"


Bomb::Bomb(sf::Vector2f playerPos) : Weapons(playerPos)	
{
	damage = 5;
	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{51,5},sf::Vector2i{6,6} });
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