#include "Boss.h"
#include<iostream>


Boss::Boss()
{
	ticks = 24; 
	if (!texture->loadFromFile("../res/Bosses.png"))
		std::cout << "Error Loaing from File"; 
	sprite->setTexture(*texture);

	sprite->setTextureRect(sf::IntRect{ sf::Vector2i(11,14), sf::Vector2i(62,79) });
	
	glideRight = new Animation(1, 3, 
		sf::IntRect{ sf::Vector2i(8,14), sf::Vector2i(200,79) });

	sprite->setPosition(sf::Vector2f(900.f, 15.f));
 
}


Boss::~Boss()
{

}


void Boss::attack()
{
	if (ticks % tickRate*2 == 0)
		sprite->setTextureRect(*glideRight->nextFrame());
}


void Boss::death()
{
	//death logic
}

void Boss::move()
{
	float ySpeed;
	ySpeed = 2 * sin(ticks / 20);

	sprite->move(sf::Vector2f(.7f, ySpeed));

	if (ySpeed > 0)
		attack();

}

void Boss::update(int input)
{
	ticks++; 
	move(); 
}