#include "Coin.h"
#include <iostream>

Coin::Coin(sf::Vector2f pos, int size)
{
	texture = new sf::Texture();

	if (!texture->loadFromFile("../res/Shop Transparent.png"))
		std::cout << "\nCoin: Error Loading from File\n";
	sprite = new sf::Sprite(*texture);

	//Determine which coin type to load 
	if (size == 1)
	{
		value = 10;
		std::cout << "\nSize 1 Coin created\n"; 
		zones.push_back(sf::IntRect(sf::Vector2i{ 429, 175 }, sf::Vector2i{ 8,8 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 439, 175 }, sf::Vector2i{ 4,8 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 446, 175 }, sf::Vector2i{ 1,8 }));
	}
	else if (size == 2)
	{
		value = 20; 
		std::cout << "\nSize 2 Coin created\n";
		zones.push_back(sf::IntRect(sf::Vector2i{ 449, 172 }, sf::Vector2i{ 13,13 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 464, 172 }, sf::Vector2i{ 7,13 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 474, 172 }, sf::Vector2i{ 2,13}));
	}

	else if (size == 3)
	{
		value = 30;
		std::cout << "\nSize 3 Coin created\n";
		zones.push_back(sf::IntRect(sf::Vector2i{ 478, 170 }, sf::Vector2i{ 16, 16 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 496, 170 }, sf::Vector2i{ 8, 16 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 506, 170 }, sf::Vector2i{ 3, 16 }));
	}


	zone = 0; 
	sprite->setTextureRect(zones.at(zone));
	sprite->setPosition(pos);
	initialHeight = pos.y; 

	bounce = true; 
	yMax = initialHeight; 
	ySpeed = 5;
	changeMax = false; 

	std::cout << "\nCoin Created\n";
	set_visible = true;
	set_active = true; 
	fullView = false; 
	

	//define where groung is 
	ground = 159.f; 
}

Coin::~Coin()
{

}


void Coin::update(int input)
{

	//Rotatation animation for the coin 
	if (ticks % 10 == 0)
	{
		if (zone == 2)
			zone = 1;
		else if (zone == 1 && !fullView)
		{
			zone++;
			fullView = true;
		}
		else if (zone == 1 && fullView)
		{
			zone--;
			fullView = false;
		}
		else
			zone++;

		sprite->setTextureRect(zones.at(zone));
	}

	if (ySpeed > 0.5)
		move();
	else
		sprite->setPosition(sf::Vector2f{ sprite->getPosition().x , 159.f }); 
	ticks++;
}


void Coin::death()
{

}

void Coin::move()
{
	if (sprite->getPosition().y >= ground && !bounce)
	{//Change Velocity based on position
		bounce = true;
		std::cout << "\n Coin hit the Ground\n";
		ySpeed *= .5;
	}
	else if (bounce && !(sprite->getPosition().y <= yMax))
	{
		//Bounce velocity 
		changeMax = true;
		sprite->move(sf::Vector2f{ 0.f,-0.5f * ySpeed });
	}
	else
	{
		//Decensing Velocity
		bounce = false;
		sprite->move(sf::Vector2f{ 0.f, ySpeed });

		if (changeMax)
		{
			yMax *= 2.5;
			changeMax = false;
		}
	}
}