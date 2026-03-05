#include "Snake.h"


Snake::Snake(bool isFaceRight) : Enemy()
{
	timer.restart();
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 120.f };
	speed = .5f;
	acceleration = 1.05f;

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
	//moves in a straight line, then charge off screen

	//After 7 seconds, speed increases by 5% every tick
	sf::Time lifeSpan = sf::seconds(7.f);

	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;
	
	if (timer.getElapsedTime() >= lifeSpan)
		speed *= acceleration;
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
	set_visible = false;
	//run death animation and remove from entities vector
	

}