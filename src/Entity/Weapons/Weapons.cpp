#include<SFML/Graphics.hpp>
#include <iostream>
#include "Weapons.h"



Weapons::Weapons(sf::Vector2f playerPos) 
{
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error Loading Image"; 

	sprite = new sf::Sprite(*texture);
	sprite->setPosition(playerPos);	
	damage = 1;
	health = 1; 
}

Weapons::~Weapons()
{

}

void Weapons::update(int input)
{
	sprite->move({1.5, 0});
}
