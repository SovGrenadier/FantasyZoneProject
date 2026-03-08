#include "Moocolon.h"
#include <iostream>
#include <cmath>

Moocolon::Moocolon(bool isFaceRight) : Enemy()
{
	timer.restart();
	faceRight = isFaceRight;
	ticks = 13;
	pos = sf::Vector2f{ 840.f,100.f };
	speed = 0.6f;
	
	//frames
	sf::IntRect zone({ 10, 37 }, { 34, 17 });
	Animation* fly = new Animation(1, 2, zone);
	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;
	animations[curAction] = fly;


	//set sprite
	sprite->setTexture(*texture);
	sprite->setTextureRect(*fly->getFrame(0));
	sprite->setPosition(pos);
}


Moocolon::~Moocolon()
{
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
}


void Moocolon::spawn()
{
	/*two different ways to spawn
	1. a group of 4 will form a square and move that way
	2. a column of 4 will move horizontally
	*/

}


void Moocolon::move()
{
	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;
}


void Moocolon::update(int input)
{
	ticks++;
	if (!alive)
	{
		if (ticks >= tickRate)
		{
			ticks = 0;

			if (curDeathFrame >= deathFrames.size())
				set_visible = false;

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
	move();
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());

		sf::FloatRect bounds = sprite->getLocalBounds();
		sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	}
	if (faceRight)
	{
		//flip sprite so its facing right
		sprite->setScale({ 1.f,1.f });
	}
	else
	{
		//flip sprite so its facing left
		sprite->setScale(sf::Vector2f(-1.f, 1.f));

	}

	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}

	sprite->setPosition(pos);

}


void Moocolon::death()
{
	alive = false;
	deathPos = pos;
}