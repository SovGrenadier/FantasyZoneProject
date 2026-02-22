#include "Bottaco.h"


Bottaco::Bottaco() : Enemy()
{
	//faceRight = isFaceRight;
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
	//comes out of spawners
}


void Bottaco::move()
{
	//move logic
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