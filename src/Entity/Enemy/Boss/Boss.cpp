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
	mouth = std::make_shared<StumpalonMouth>(sf::Vector2f(900.f, 15.f));
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

void Boss :: move()
{
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		//handled through player
		//std::cout << "test" << std::endl;
		//viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
	}
	float ySpeed;
	ySpeed = 2 * sin(ticks / 20);

	sprite->move(sf::Vector2f(.7f, ySpeed));

	if (ySpeed > 0)
		attack();
 
}

void Boss::update(int input)
{
	if(ticks==24)
		mouth->initialize(); 

	ticks++; 
	move();
}