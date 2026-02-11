#include<SFML/Graphics.hpp>
#include <iostream>
#include "../Weapons/Weapons.h"


Weapons::Weapons() : Entity()
{
	texture = new sf::Texture(); 
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error"; 

	sprite = new sf::Sprite(*texture);
	sprite->setPosition(sf::Vector2f{ 175.f, 220.f });	
	damage = 1;
	health = 1; 
}

Weapons::~Weapons()
{

}

void Weapons::update(int input)
{
	pos += velocity; 
	sprite->setPosition(pos);
}