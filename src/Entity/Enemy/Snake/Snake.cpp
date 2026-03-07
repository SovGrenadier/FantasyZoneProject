#include "Snake.h"


Snake::Snake(bool isFaceRight) : Enemy()
{
	set_visible = true;
	set_active = true;
	curDeathFrame = 0;
	timer.restart();
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 120.f };
	speed = .6f;
	acceleration = 1.05f;

	sf::IntRect zone({ 9, 76 }, { 78, 15 });
	Animation* fly = new Animation(1,3, zone);


	//add 4 death frames
	deathFrames.push_back(sf::IntRect({ 11,419 }, { 8,8 }));
	deathFrames.push_back(sf::IntRect({ 21,417 }, { 12,12 }));
	deathFrames.push_back(sf::IntRect({ 35,415 }, { 16,16 }));
	deathFrames.push_back(sf::IntRect({ 11,419 }, { 8,8 }));
	

	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;
	
	animations[curAction] = fly;

	
	sprite->setTexture(*texture);
	sprite->setTextureRect(*fly->getFrame(0));
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
	if (!alive)
	{
		
		if (ticks >= tickRate)
		{
			ticks = 0;
			
			if (curDeathFrame >= deathFrames.size())
				set_visible = false;

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
	if(ticks >= tickRate)
	{
		
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}

	sprite->setPosition(pos);
}


void Snake::death()
{
	alive = false;
	deathPos = pos;
	//run death animation and remove from entities vector
}