#include<SFML/Graphics.hpp>
#include <iostream>
#include "../Weapons/Weapons.h"


Weapons::Weapons(sf::Vector2f playerPos) : Entity()
{
	texture = new sf::Texture(); 
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error"; 

	sprite = new sf::Sprite(*texture);
	sprite->setPosition(playerPos);	
	damage = 1;
	health = 1; 
}

Weapons::~Weapons()
{

}

void Weapons::update()
{
	pos += velocity; 
	sprite->setPosition(pos);
}
