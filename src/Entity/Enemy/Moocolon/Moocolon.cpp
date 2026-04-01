#include "Moocolon.h"
#include <iostream>
#include <cmath>

Moocolon::Moocolon(bool isFaceRight, sf::View* view) : Enemy()
{
	timer.restart();
	faceRight = isFaceRight;
	ticks = 13;
	pos = sf::Vector2f{ 840.f,100.f };
	
	//frames
	sf::IntRect zone({ 10, 37 }, { 34, 17 });
	Animation* fly = new Animation(1, 2, zone);
	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;
	animations[curAction] = fly;


	centerY = pos.y;
	speed = 0.6f;
	amplitude = 25.f;
	time = 0.f;
	bounceIndex = 0;
	previousY = pos.y;
	bounce = false;
	bounceTwice = false;
	bounceCount = 0;

	viewport = view;
	//set sprite
	sprite->setTexture(*texture);
	sprite->setTextureRect(*fly->getFrame(0));
	sprite->setPosition(pos);
}


Moocolon::~Moocolon()
{
	std::cout << "Moocolon destroyed\n";
}


void Moocolon::spawn()
{
	set_active = true;
	set_visible = true;
	/*two different ways to spawn
	1. a group of 4 will form a square and move that way
	2. a column of 4 will move horizontally
	*/

}

//to-do: fix not moving at all after reaching centerY
void Moocolon::move()
{
	if (bounceCount == 1)
	{
		if ((previousY < centerY + 1.f) && (previousY > centerY - 1.f))
			if (faceRight)
				pos.x += speed;
			else
				pos.x -= speed;
		return;
	}
	float wave = static_cast<float>(sin(time));

	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;


	if(previousY < (centerY + amplitude * wave)) //if moocolon y pos decreasing
		if ((previousY < centerY + 1.f) && (previousY > centerY - 1.f)) 
		{ // if moocolon pos y is in range of centerY
			bounceIndex++;
			if (bounceIndex % 2 == 0)
			{
				bounce = true;
				bounceCount++;
			}
		}

	if (bounce)
		time *= -1.f;
	else
		time *= 1.f;

	pos.y = centerY + amplitude * wave;
	bounce = false;

	if (time == 0.f)
		if (faceRight)
			time += 0.05f;
		else
			time -= 0.05f;
	else if (time > 0.f)
		time += 0.05f;
	else if (time < 0.f)
		time -= 0.05f;
	sprite->setPosition(pos);
	previousY = pos.y;
}


void Moocolon::update(int input)
{
	if (!isOnScreen(*viewport))
	{
		set_active = false;
		set_visible = false;
		return;
	}
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
	move();
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
		sf::FloatRect bounds = sprite->getLocalBounds();
		sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	}
	sprite->setPosition(pos);
}


void Moocolon::death()
{
	alive = false;
	deathPos = pos;
}