#include "Moocolon.h"
#include <iostream>

Moocolon::Moocolon()
{
	if (!(texture->loadFromFile("../res/Enemies.png")))
		std::cout << "ERROR: Moocolon TEXTURE UPLOAD FAILED\n";
	else
		sprite = new sf::Sprite(*texture);

	//Animation* fly = new Animation();
	
	sprite->setTexture(*texture);
	sprite->setPosition(pos);
}


Moocolon::~Moocolon()
{
	delete sprite;
	delete texture;
}


void Moocolon::spawn()
{
	/*two different ways to spawn
	1. a group of 4 will form a square and move that way
	2. a column of 4 will move horizontally
	*/

}


void Moocolon::move()
{
	//move like a sinusoidal function regardless of formation
}