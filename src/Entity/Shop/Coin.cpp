#include "Coin.h"
#include <iostream>


/// <summary> 
/// Creates a coin obejct that spawn is the position of the entity that lauched it
/// </summary> 
/// <param name = "pos"></param>
/// <param name = "size"></param> 
Coin::Coin(sf::Vector2f pos, int size)
{
	//set up sprite 
	texture = new sf::Texture();

	if (!texture->loadFromFile("../res/Shop Transparent.png"))
		std::cout << "\nCoin: Error Loading from File\n";
	sprite = new sf::Sprite(*texture);

	//Determine which coin type to load 
	if (size == 1)
	{
		value = 100;
		zones.push_back(sf::IntRect(sf::Vector2i{ 429, 175 }, sf::Vector2i{ 8,8 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 439, 175 }, sf::Vector2i{ 4,8 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 446, 175 }, sf::Vector2i{ 1,8 }));
	}
	else if (size == 2)
	{
		value = 200;
		zones.push_back(sf::IntRect(sf::Vector2i{ 449, 172 }, sf::Vector2i{ 13,13 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 464, 172 }, sf::Vector2i{ 7,13 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 474, 172 }, sf::Vector2i{ 2,13}));
	}

	else if (size == 3)
	{
		value = 300;
		zones.push_back(sf::IntRect(sf::Vector2i{ 478, 170 }, sf::Vector2i{ 16, 16 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 496, 170 }, sf::Vector2i{ 8, 16 }));
		zones.push_back(sf::IntRect(sf::Vector2i{ 506, 170 }, sf::Vector2i{ 3, 16 }));
	}

	// Set the sprite to its starting fram 
	zone = 0; 
	sprite->setTextureRect(zones.at(zone));
	sprite->setPosition(pos);

	//Initialize variables 
	initialHeight = pos.y; 
	bounce = true;
	yMax = initialHeight; 
	ySpeed = 5;
	changeMax = false; 
	set_visible = true;
	set_active = true; 
	fullView = false; 

	//define where ground is 
	ground = 159.f; 
}


Coin::~Coin()
{

}


/// <summary> 
/// Animates the coin and initiates movement.
/// </summary> 
/// <param name = "input"></param> 
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

	//Move only when the coin has a substantial velocity. Else leave the coin on the ground 
	if (ySpeed > 0.5)
		move();
	else
		sprite->setPosition(sf::Vector2f{ sprite->getPosition().x , 159.f }); 
	
	ticks++;
}


void Coin::death()
{
}


/// <summary> 
/// Changes the coin's velocity based on bounce
/// </summary> 
void Coin::move()
{
	if (sprite->getPosition().y >= ground && !bounce)
	{
		bounce = true;
		ySpeed *= .5;

		// Reduce the coin's maximum height with every bouce 
		if (firstBounce)
		{
			yMax = 120.f;
			firstBounce = false;
		}
		else
			yMax *= 1.50;

	}
	else if (bounce && !(sprite->getPosition().y <= yMax))
	{
		//Move the coin upward after it hits the ground 
		changeMax = true;
		sprite->move(sf::Vector2f{ 0.f,-0.5f * ySpeed });
	}
	else
	{
		//Move the coin downward after it hits its max height
		bounce = false;
		sprite->move(sf::Vector2f{ 0.f, ySpeed });

	}
}
