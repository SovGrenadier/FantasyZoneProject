#include "StumpalonMouth.h"
#include <iostream>

StumpalonMouth::StumpalonMouth(sf::Vector2f pos)
{
	ticks = 24; 
	frame = 0; 
	health = 48;


	if (!texture->loadFromFile("../res/Boss.png"))
		std::cout << "Error Loaing from File";
	sprite->setTexture(*texture);

	zone = sf::IntRect(sf::Vector2i{ 213, 33 }, sf::Vector2i{ 18,63});
	set_visible = false; 

	changeColor = new Animation{ 3, 2, zone };
	sprite->setTextureRect(*changeColor->getFrame(0));

	sprite->setPosition(sf::Vector2f{ pos.x+1, pos.y + 34 }); 
}

StumpalonMouth::~StumpalonMouth()
{

}

void StumpalonMouth::setVisibility(bool state)
{
	set_visible = state; 
}

void StumpalonMouth::changeState()
{

	if (frame == 4)
		frame = 1;
	else
		frame += 2;

	if(frame<=5)
		sprite->setTextureRect(*changeColor->getFrame(frame));
	else
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(231, 54), sf::Vector2i(12, 23)));
}

void StumpalonMouth::update(int input)
{
	ticks++; 
	move(); 
}

void StumpalonMouth::move()
{
	//Ensures sprite doesn't disappear when the viewport loops
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	float ySpeed;
	ySpeed = -sin((ticks * PI) / 100);

	sprite->move(sf::Vector2f(.7f, ySpeed));

}

void StumpalonMouth::takeDamage(int damage)
{
	health -= damage; 

	if (health == 36)
		set_visible = true;
	else if (health % 6 == 0)
		changeState();
		
}

void StumpalonMouth::death()
{
	set_active = false;
	alive = false; 
}