#include "Boss.h"
#include<iostream>
#include <time.h>


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
	sprite->setPosition(sf::Vector2f(900.f, 75.f));
 
}


Boss::~Boss()
{

}


void Boss::attack()
{
	int leafs; 
	leafs = rand() % 5 +1; 
	for(int i=0; i<leafs; i++)
		std::make_shared<Leaf>(sf::Vector2f{ sprite->getPosition().x, sprite->getPosition().y + 39 })->initialize();
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
	ySpeed =  - sin((ticks * PI) / 100);

	sprite->move(sf::Vector2f(.7f, ySpeed ));

	if (ticks % 50 == 0)
	{
		if (frame == 3)
		{
			sprite->setTextureRect(*glideRight->getFrame(1));
			frame = 0; 
		}
		else
		{
			sprite->setTextureRect(*glideRight->getFrame(frame));
			frame++;
		}
	}
	/*
	if (sprite->getTextureRect() == *glideRight->getFrame(2) && ticks % 7 == 0);
		//attack();

	if (sprite->getTextureRect() == *glideRight->getFrame(0))
		mouth->setVisibility(true);
	else
		//mouth->setVisibility(false);
		;
		*/
 
}

void Boss::update(int input)
{
	/*
	if (ticks == 24)
	{
		//mouth = std::make_shared<StumpalonMouth>(sprite->getPosition());
		mouth->initialize();
	}
	*/
	ticks++; 
	move();
}