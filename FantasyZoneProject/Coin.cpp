#include "Coin.h"
#include <iostream>

Coin::Coin(sf::Vector2f pos, int size)
{
	texture = new sf::Texture(); 

	if (!texture->loadFromFile("../../res/Shop Transparent.png"))
		std::cout << "\nCoin: Error Loading from File\n";
	else
		std::cout << "It Works!\n"; 

	//sprite->setTexture(*texture); 
	if(size == 1)
		zone = sf::IntRect(sf::Vector2i{ 444, 186 }, sf::Vector2i{ 21,13 });
	else if (size ==2)
		zone = sf::IntRect(sf::Vector2i{ 477, 186 }, sf::Vector2i{ 29,15 });
	else if (size == 3)
		zone = sf::IntRect(sf::Vector2i{ 510, 186 }, sf::Vector2i{ 34, 18 });

	//sprite->setTextureRect(zone); 

	initialHeight = pos.y; 
}

Coin::~Coin()
{

}


void Coin::update(int input)
{

}


void Coin::death()
{

}

void Coin::move()
{
	if (sprite->getPosition().y <= ground && !bounce)
		bounce = true;
	else if (bounce && !(sprite->getPosition().y >= yMax))
	{
		changeMax = true; 
		sprite->move(sf::Vector2f{ 0.f,-0.3f }); 
	}
	else
	{
		bounce = false; 
		sprite->move(sf::Vector2f{ 0.f, 0.5f });

		if (changeMax)
		{
			yMax *= .5; 
			changeMax = false; 
		}
	}
}