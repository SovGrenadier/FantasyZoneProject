#include "Kirikiri.h"


Kirikiri::Kirikiri(bool isFaceRight) : Enemy()
{
	faceRight = isFaceRight;
	ticks = 12;
	pos = { 840.f,50.f };

	sprite->setTexture(*texture);
	sprite->setPosition(pos);

	sf::IntRect zone({ 8, 20 }, { 51, 15 });
	Animation* fly = new Animation(1, 3, zone);

	curAction = FLY_RIGHT;
	animations[curAction] = fly;
}


Kirikiri::~Kirikiri()
{

}


void Kirikiri::spawn()
{

}


void Kirikiri::move()
{

}


void Kirikiri::update(int)
{
	ticks++;
	move();
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());

	}
}


void Kirikiri::death()
{

}