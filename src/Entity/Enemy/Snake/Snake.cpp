#include "Snake.h"


Snake::Snake(bool isFaceRight) : Enemy()
{
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 50.f };

	//FIX PIXEL CLIPPING OF FRAMES
	sf::IntRect zone({ 10, 76 }, { 76, 15 });
	Animation* fly = new Animation(1,3, zone);

	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;
	
	animations[curAction] = fly;

	sprite->setTexture(*texture);
	sprite->setPosition(pos);
}


Snake::~Snake()
{

}


void Snake::spawn()
{

}


void Snake::move()
{

}


void Snake::update(int input) 
{
	ticks++;
	move();
	if(ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}

	sprite->setPosition(pos);
}


void Snake::death()
{

}