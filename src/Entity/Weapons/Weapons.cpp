#include<SFML/Graphics.hpp>
#include <iostream>
#include "Weapons.h"



Weapons::Weapons(sf::Vector2f playerPos) 
{
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error Loading Image"; 

	sprite = new sf::Sprite(*texture);
	sprite->setPosition(playerPos);	
	damage = 1;
	ownWeapon = true;
}

Weapons::~Weapons()
{

}
