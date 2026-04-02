#include "Kirikiri.h"
#include<iostream>


Kirikiri::Kirikiri(bool isFaceRight, sf::Vector2f newPos) : Enemy()
{
	//same speed as player
	faceRight = isFaceRight;
	ticks = 12;
	speed.x = 0.6f;
	pos = newPos;
	
	sf::IntRect zone({ 8, 20 }, { 51, 15 });
	Animation* flyRight = new Animation(1, 3, sf::IntRect{ sf::Vector2i{8,20},sf::Vector2i{51,15} });
	Animation* flyLeft = new Animation(1, 3, sf::IntRect{ sf::Vector2i{132,21},sf::Vector2i{51,15} });

	animations[FLY_RIGHT] = flyRight;
	animations[FLY_LEFT] = flyLeft;

	if(faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;

	sprite->setTexture(*texture);
	sprite->setPosition({ pos.x + 20.f,pos.y + 10.f });

}


Kirikiri::~Kirikiri()
{

}


void Kirikiri::move()
{
	/*
	* COMES OUT OF SPAWN DOWN, THEN MOVES TO EDGE OF SCREEN WHERE IT
	* TURNS AROUND AND THEN CHARGES IN OPPOSITE DIRECTION
	* OR 
	* COMES OUT OF SPAWN DOWN, THEN MOVES IN ONE DIRECTION AND 
	* WILL CHARGE IN THAT DIRECTION AFTER A CERTAIN AMOUNT OF TIME/DISTANCE
	*/




}


void Kirikiri::update(int) 
{
	ticks++;
	if (!alive)
	{
		if (ticks >= tickRate)
		{
			ticks = 0;

			if (curDeathFrame >= deathFrames.size())
			{
				set_active = false;
				set_visible = false;
			}

			else
			{
				//change sprite
				sprite->setTextureRect(deathFrames.at(curDeathFrame));
				//set origin
				sf::FloatRect bounds = sprite->getLocalBounds();
				sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
				//set position back regardless of change due to origin
				sprite->setPosition(deathPos);
				//advance to next death frame
				curDeathFrame++;
			}
		}
		return;
		//exit method so sprite doesn't get updated further
	}
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
		if (disTraveled < 10.f)
		{
			sprite->move({ 0.0f,1.0f });
			disTraveled += 1.0f;
		}
		else if (disTraveled < 300.f)
		{
			if (faceRight)
			{
				sprite->move({ 1.0f,0.0f });
			}
			else
			{
				sprite->move({ -1.0f,0.0f });
			}
		}
		if (sprite->getPosition().x + sprite->getGlobalBounds().size.x < viewport->getCenter().x - 125.f)
		{
			set_active = false;
			set_visible = false;
		}
		if (sprite->getPosition().x > viewport->getCenter().x + 125.f)
		{
			set_active = false;
			set_visible = false;
		}
		//sf::FloatRect bounds = sprite->getLocalBounds();
		//sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	}
}


void Kirikiri::death()
{
	alive = false;
	deathPos = pos;
}