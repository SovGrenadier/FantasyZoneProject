#include "Bomb.h"


Bomb::Bomb(sf::Vector2f playerPos, bool faceRight) : Weapons(playerPos)	
{
	damage = 5;
	direction = faceRight;
	if(direction)
		sprite->setTextureRect(sf::IntRect{ sf::Vector2i{62,28},sf::Vector2i{9,7} });
	else
		sprite->setTextureRect(sf::IntRect{ sf::Vector2i{43,141},sf::Vector2i{9,7} });
}


Bomb::~Bomb()
{
}


void Bomb::death()
{
	set_active = false;
	set_visible = false;
}
//equation to get bomb motion is 25*0.5x^2
void Bomb::update(int input)
{
	sprite->move({ 0, 1.5 });
}