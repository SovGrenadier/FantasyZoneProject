#include "Kirikiri.h"


Kirikiri::Kirikiri(bool isFaceRight) : Enemy()
{
	//same speed as player
	faceRight = isFaceRight;
	ticks = 12;
	pos = { 840.f, 80.f };
	speed.x = 0.6f;
	
	
	sf::IntRect zone({ 8, 20 }, { 51, 15 });
	Animation* fly = new Animation(1, 3, zone);

	curAction = FLY_RIGHT;
	animations[curAction] = fly;

	sprite->setTexture(*texture);
	sprite->setPosition(pos);

}


Kirikiri::~Kirikiri()
{

}


void Kirikiri::spawn()
{

}


void Kirikiri::move()
{
	/*
	* COMES OUT OF SPAWN DOWN, THEN MOVES TO EDGE OF SCREEN WHERE IT
	* TURNS AROUND AND THEN CHARGES IN OPPOSITE DIRECTION
	* OR 
	* COMES OUT OF SPAWN DOWN, THEN MOVES IN ONE DIRECTION AND 
	* WILL CHARGE IN THAT DIRECTION AFTER A CERTAIN AMOUNT OF TIME/DISTANCE
	*/




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