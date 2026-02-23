#include "Snake.h"


Snake::Snake(bool isFaceRight) : Enemy()
{
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 150.f };
	speed = .5f;

	//FIX PIXEL CLIPPING OF FRAMES
	sf::IntRect zone({ 9, 76 }, { 78, 15 });
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
	//move in a straight line, then charge off screen

	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;

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