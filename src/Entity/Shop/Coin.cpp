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
		zone = sf::IntRect(sf::Vector2i{ 448, 185 }, sf::Vector2i{ 21,13 });
		value = 10;
	}
	else if (size == 2)
	{
		zone = sf::IntRect(sf::Vector2i{ 477, 186 }, sf::Vector2i{ 29,15 });
		value = 20; 
	}
	else if (size == 3)
	{
		zone = sf::IntRect(sf::Vector2i{ 510, 186 }, sf::Vector2i{ 34, 18 });
		value = 30;
	}
	
	sprite->setTextureRect(zone); 
	sprite->setPosition(pos); 
	initialHeight = pos.y; 

	bounce = true; 
	yMax = initialHeight; 
	changeMax = false; 
}

Coin::~Coin()
{

}


void Coin::update(int input)
{
	move(); 
}


void Coin::death()
{

}

void Coin::move()
{
	
	if (sprite->getPosition().y <= ground && !bounce)//Change Velocity based on position
		bounce = true;
	else if (bounce && !(sprite->getPosition().y >= yMax))
	{
		//Bounce velocity 
		changeMax = true; 
		sprite->move(sf::Vector2f{ 0.f,-0.3f }); 
	}
	else
	{
		//Decensing Velocity
		bounce = false; 
		sprite->move(sf::Vector2f{ 0.f, 0.5f });

		if (changeMax)
		{
			yMax *= .5; 
			changeMax = false; 
		}
	}
}