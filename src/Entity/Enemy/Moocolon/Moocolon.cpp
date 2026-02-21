#include "Moocolon.h"
#include <iostream>
#include <cmath>

Moocolon::Moocolon(bool isFaceRight) : Enemy()
{
	faceRight = isFaceRight;
	ticks = 13;
	pos = sf::Vector2f{ 840.f,30.f };
	//840 is center of screen
	//frames
	sf::IntRect zone({ 10, 37 }, { 34, 17 });
	Animation* fly = new Animation(1, 2, zone);
	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;
	animations[curAction] = fly;

	//needed for movement
	speed = .5f;
	amplitude = 10.f;
	frequency = 0.1f;
	time = 0.f;
	baseY = pos.y;

	//set sprite
	sprite->setTexture(*texture);
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
	//move like a sinusoidal func, until it charges in a straight line
	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;                               
	
	time += 0.05f;          

	float wave = static_cast<float>(sin(time));
	pos.y = baseY + amplitude * wave;

	sprite->setPosition(pos);
}


void Moocolon::update(int input)
{
	ticks++;
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
	}

	sprite->setPosition(pos);


	
}


void Moocolon::death()
{
	set_visible = false;
}