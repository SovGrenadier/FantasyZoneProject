#include "Boss.h"
#include<iostream>
#include <time.h>

/// <summary>
/// Creates a boss object relative to the player's position
/// </summary>
/// <param name="playerPos"></param>
Boss::Boss(float playerXPos)
{ 
	ticks = 24; 

	if (!texture->loadFromFile("../res/Bosses.png"))
		std::cout << "Error Loaing from File"; 

	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect{ sf::Vector2i(11,14), sf::Vector2i(62,79) });
	
	glideRight = new Animation(1, 3, 
		sf::IntRect{ sf::Vector2i(8,14), sf::Vector2i(200,79) });

	sprite->setPosition(sf::Vector2f(playerXPos + 80.f, 75.f));
}


Boss::~Boss()
{

}


void Boss::attack()
{
	int leafs; 
	leafs = rand() % 5 +1; 
	for(int i=0 ; i<leafs; i++)
		std::make_shared<Leaf>(sf::Vector2f{ sprite->getPosition().x,
			sprite->getPosition().y + 39 })->initialize();
}



void Boss::death()
{
	alive = false;
	set_active = false;
}

void Boss :: move()
{
	//Ensures sprite doesn't disappear when the viewport loops
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
}

void Boss::update(int input)
{
	if (ticks == 24)
	{
		mouth = std::make_shared<StumpalonMouth>(sprite->getPosition());
		mouth->initialize();
	}

	if (mouth->getHealth() == 0)
	{
		mouth->death();
		death();
	}

	move();

	if (ticks % 50 == 0)
	{
		if (frame == OPEN_MOUTH)
		{
			openning = false; 
			sprite->setTextureRect(*glideRight->getFrame(OPEN_MOUTH));
			frame--;
		}
		else if (frame == CLOSED_MOUTH)
		{
			openning = true;
			sprite->setTextureRect(*glideRight->getFrame(CLOSED_MOUTH));
			frame++;
		}
		else if (frame==AJAR_MOUTH)
		{
			sprite->setTextureRect(*glideRight->getFrame(AJAR_MOUTH));

			if (openning)
				frame++;
			else
				frame--; 
		}
	}

	if (sprite->getTextureRect() == *glideRight->getFrame(OPEN_MOUTH) && ticks % 7 == 0) 
		attack();

	if (sprite->getTextureRect() == *glideRight->getFrame(CLOSED_MOUTH) && mouth->getHealth() <= 42)
		mouth->setVisibility(true);
	else
		mouth->setVisibility(false);

	ticks++;
}


int Boss :: getHealth()
{
	if (mouth == nullptr)
		return 1000;
	else
		return mouth->getHealth();
}
