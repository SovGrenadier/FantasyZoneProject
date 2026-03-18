#include "Kirikiri.h"


Kirikiri::Kirikiri(bool isFaceRight, sf::Vector2f pos) : Enemy()
{
	//same speed as player
	faceRight = isFaceRight;
	ticks = 12;
	speed.x = 0.6f;
	
	
	sf::IntRect zone({ 8, 20 }, { 51, 15 });
	Animation* flyRight = new Animation(1, 3, sf::IntRect{ sf::Vector2i{8,20},sf::Vector2i{51,15} });
	Animation* flyLeft = new Animation(1, 3, sf::IntRect{ sf::Vector2i{132,21},sf::Vector2i{51,15} });

	curAction = FLY_RIGHT;
	animations[curAction] = flyRight;
	animations[FLY_LEFT] = flyLeft;

	sprite->setTexture(*texture);
	sprite->setPosition(pos);

}


Kirikiri::~Kirikiri()
{

}


void Kirikiri::spawn(sf::Vector2f spawnpos)
{
	pos = spawnpos;
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
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
		
		sf::FloatRect bounds = sprite->getLocalBounds();
		sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	}

	if (faceRight)
		sprite->setScale({ 1.f,1.f });
	else
		sprite->setScale({ -1.f,1.f });

	sprite->setPosition(pos);
}


void Kirikiri::death()
{
	alive = false;
	deathPos = pos;
}