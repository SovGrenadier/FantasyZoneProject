#include "Bomb.h"
#include<iostream>


Bomb::Bomb(sf::Vector2f playerPos, bool faceRight) : Weapons(playerPos)	
{
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error Loading Image";
	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);

	ownWeapon = true;
	damage = 5;

	direction = faceRight; 

	if(direction)
		sprite->setTextureRect(sf::IntRect{ sf::Vector2i{62,28},sf::Vector2i{9,7} });
	else
		sprite->setTextureRect(sf::IntRect{ sf::Vector2i{43,141},sf::Vector2i{9,7} });
	

	//Define the position of the ground to deactive bomb if it touches it 
	ground.position = { 33.f, 176.f };
	ground.size = { 1348.f , 60.f };


	viewStart = viewport->getCenter();

	start = playerPos;
	height = playerPos.y;
	sprite->setPosition(start);
	xPos = 0;
	yPos = playerPos.y;
}


Bomb::~Bomb()
{
	delete sprite;
	delete texture;
}


void Bomb::death()
{
	set_active = false;
	set_visible = false;
	alive = false; 
}


//equation to get bomb motion is -(starting height)+0.5x^2
void Bomb::update(int input)
{
	if (health <= 0)
		death();
	else if (!isOnScreen(*viewport))
		death(); 

	//Determine the velocity of the bomb based on direction 
	if (direction)
	{
		xPos++;
		yPos = height + (0.05 * xPos * xPos);
	}
	else
	{
		xPos--;
		yPos = height + (0.05 * xPos * xPos);
	}

	sprite->setPosition({ start.x+xPos+(viewport->getCenter().x-viewStart.x),yPos});

	//If the bomb is on the ground, deactivate it.
	if (ground.findIntersection(sprite->getGlobalBounds()) != std::nullopt)
	{
		set_active = false;
		set_visible = false;
	}

	if (sprite->getPosition().x > (viewport->getCenter().x + 130.f))
	{
		set_active = false;
		set_visible = false;
	}

	if (sprite->getPosition().x < (viewport->getCenter().x - 130.f))
	{
		set_active = false;
		set_visible = false;
	}
}