#include "Bomb.h"
#include<iostream>


Bomb::Bomb(sf::Vector2f playerPos, bool faceRight) : Weapons(playerPos)	
{
	damage = 5;
	direction = faceRight;
	if(direction)
		sprite->setTextureRect(sf::IntRect{ sf::Vector2i{62,28},sf::Vector2i{9,7} });
	else
		sprite->setTextureRect(sf::IntRect{ sf::Vector2i{43,141},sf::Vector2i{9,7} });
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
}


void Bomb::death()
{
	set_active = false;
	set_visible = false;
}


//equation to get bomb motion is -(starting height)+0.5x^2
void Bomb::update(int input)
{
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
	if (ground.findIntersection(sprite->getGlobalBounds()) != std::nullopt)
	{
		active = false;
	}
}