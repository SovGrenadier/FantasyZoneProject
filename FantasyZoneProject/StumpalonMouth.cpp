#include "StumpalonMouth.h"
#include <iostream>

StumpalonMouth::StumpalonMouth(sf::Vector2f pos)
{
	ticks = 24; 
	if (!texture->loadFromFile("../res/Bosses.png"))
		std::cout << "Error Loaing from File";
	sprite->setTexture(*texture);

	zone = sf::IntRect(sf::Vector2i{ 213, 33 }, sf::Vector2i{ 18,63});
	set_visible = false; 

	changeColor = new Animation{ 3, 2, zone };
	sprite->setTextureRect(*changeColor->getFrame(0));

	sprite->setPosition(sf::Vector2f{ pos.x+1, pos.y + 34 }); 

	health = 24; 
}

StumpalonMouth::StumpalonMouth()
{

}

void StumpalonMouth::setVisibility(bool state)
{
	set_visible = state; 
}

void StumpalonMouth::changeState()
{
	sprite->setTextureRect(*changeColor->nextFrame());
}

void StumpalonMouth::update(int input)
{
	ticks++; 
	move(); 
}

void StumpalonMouth::move()
{
	float ySpeed;
	ySpeed = -sin((ticks * PI) / 100);

	sprite->move(sf::Vector2f(.7f, ySpeed));

}

void StumpalonMouth::takeDamage(int damage)
{
	health -= damage; 

	if (health == 18)
		set_visible = true; 

	if (health % 6 == 0)
		changeState(); 

	std::cout << "Damage: " << damage << std::endl; 
}