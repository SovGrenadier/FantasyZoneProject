#include "Scissors.h"


Scissors::Scissors(bool isFaceRight) : Enemy()
{
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 50.f };

	//FIX PIXEL CLIPPING OF FRAMES
	sf::IntRect zone({ 10, 4 }, { 76, 16 });
	Animation* fly = new Animation(1,4,zone);

	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;

	animations[curAction] = fly;

	sprite->setTexture(*texture);
	sprite->setPosition(pos);
}


Scissors::~Scissors()
{

}


void Scissors::spawn() 
{

}


void Scissors::move()
{

}


void Scissors::update(int input)
{
	ticks++;
	move();
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}

	sprite->setPosition(pos);
}


void Scissors::death()
{

}