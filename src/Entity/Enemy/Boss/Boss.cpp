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

void Boss::move()
{
	float ySpeed;
	ySpeed =  - sin((ticks * PI) / 100);

	sprite->move(sf::Vector2f(.7f, ySpeed ));

	if (ticks % 50 == 0)
	{
		frame++;
		if (frame == 3)
		{
			frame=1;
			sprite->setTextureRect(*glideRight->getFrame(frame));
			frame = -1; 
		}
		else 
			sprite->setTextureRect(*glideRight->getFrame(frame));
	}

	if (sprite->getTextureRect() == *glideRight->getFrame(2) && ticks%7==0)
		attack();

}

void Boss::update(int input)
{
	ticks++; 
	move();
}