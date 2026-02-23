#include "Bottaco.h"


Bottaco::Bottaco(bool isFaceRight) : Enemy()
{
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 30.f };

	sf::IntRect zone({10, 55}, {63, 20});
	Animation* fly = new Animation(1, 3, zone);

	curAction = FLY_RIGHT;
	animations[curAction] = fly;

	sprite->setTexture(*texture);
	sprite->setPosition(pos);
}


Bottaco::~Bottaco()
{
}


void Bottaco::spawn()
{

}


void Bottaco::move()
{
	//move logic
	//moves like a figure 8/infinity symbol
	//Two different formations
	/*
	1st Formation:
	one enemy enters from both side of ths screen, 
	they come towards the middle following the 
	figure 8 shape, then go off screen
	2nd Formation:
	a column of 4 enemy appears from one side of the screen
	follow the same movement
	*/

	sprite->setPosition(pos);
}


void Bottaco::update(int input)
{
	ticks++;
	move();
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}
}


void Bottaco::death()
{

}