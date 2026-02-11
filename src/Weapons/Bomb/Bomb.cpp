#include "Bomb.h"


Bomb::Bomb(sf::Vector2f playerPos) : Weapons(playerPos)	
{
	velocity = sf::Vector2f(0.f, 5.f);
	damage = 5;
}


Bomb::~Bomb()
{
}


