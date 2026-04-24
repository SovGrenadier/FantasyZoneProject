#include "Kirikiri.h"
#include<iostream>
#include<algorithm>
#include<cmath>


Kirikiri::Kirikiri(bool isFaceRight, sf::Vector2f newPos) : Enemy()
{
	//same speed as player
	faceRight = isFaceRight;
	ticks = 6;
	tickRate = 6;
	viewPos = viewport->getCenter().x;
	speed = -1.f;
	pos = newPos;

	Animation* flyRight = new Animation(1, 3, sf::IntRect{ sf::Vector2i{8,20},sf::Vector2i{51,15} });
	Animation* flyLeft = new Animation(1, 3, sf::IntRect{ sf::Vector2i{132,21},sf::Vector2i{51,15} });
	Animation* deathAnim = new Animation();
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));
	deathAnim->addFrame(sf::IntRect({ 21,417 }, { 12,12 }));
	deathAnim->addFrame(sf::IntRect({ 35,415 }, { 16,16 }));
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));

	animations[FLY_RIGHT] = flyRight;
	animations[FLY_LEFT] = flyLeft;
	animations[DEATH] = deathAnim;

	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;

	sprite->setTexture(*texture);
	sprite->setTextureRect(*animations[curAction]->getFrame(0));
	sprite->setPosition({ pos.x + 20.f,pos.y + 10.f });
}


Kirikiri::~Kirikiri()
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
	//Ensures sprite doesn't disappear when the viewport loops
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
		viewportLoop = true;
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		//handled through player
		//std::cout << "test" << std::endl;
		//viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
		viewportLoop = true;
	}
	speed = 1.5;
	ticks++;
	if (!alive)
	{
		if (ticks >= tickRate)
		{
			ticks = 0;

			if (curDeathFrame >= animations[DEATH]->getFrameCount())
			{
				set_active = false;
				set_visible = false;
			}

			else
			{
				//change sprite
				sprite->setTextureRect(*(animations[DEATH]->getFrame(curDeathFrame)));
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
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}
	if (disTraveled < 20.f)
	{
		sprite->move({ 0.0f,1.0f });
		disTraveled += 1.0f;
	}
	else if (disTraveled < 600.f)
	{
		if (sprite->getPosition().x + sprite->getGlobalBounds().size.x > viewport->getCenter().x + 105.f && faceRight && !switchLeft)
		{
			switchLeft = true;
			disTravelTemp = disTraveled;
		}

		if (sprite->getPosition().x < viewport->getCenter().x - 105.f && !faceRight&&!switchRight)
		{
			switchRight = true;
			disTravelTemp = disTraveled;
		}

		
		if (switchRight)
		{
			//ticks = 0;
			//for testing and debugging
			//std::cout << disTraveled << ' ' << disTravelTemp << std::endl;
			//std::cout << "xPos:" << sprite->getPosition().x << ' ' << "yPos:" << sprite->getPosition().y << std::endl;
			//std::cout << "xMov:" << (float)(-1 * (1 / 2.0) * speed) << std::endl;
			if (disTraveled > disTravelTemp + 12*speed)
			{
				switchRight = false;
			}
			else
			{
				if (disTraveled < disTravelTemp + 7*speed)
				{
					//moves along hypotenuse of length speed, 30,60,90 right triangle
					sprite->move({ (float)(-1 * (1 / 2.0)*speed), (float)(-1 * (sqrt(3) / 2)*speed) });
					disTraveled += speed;
					faceRight = true;
					curAction = FLY_RIGHT;
					ticks = 6;
				}
				else
				{
					//moves along hypotenuse of length speed, 30,60,90 right triangle
					sprite->move({ (float)(1 * (1 / 2.0) * speed), (float)(-1 * (sqrt(3) / 2) * speed) });
					disTraveled += speed;
				}
			}
			//std::cout << "test"<<std::endl;
		}
		else if (switchLeft)
		{
			if (disTraveled > disTravelTemp + 12 * speed)
			{
				switchLeft = false;
			}
			else
			{
				if (disTraveled < disTravelTemp + 7 * speed)
				{
					//moves along hypotenuse of length speed, 30,60,90 right triangle
					sprite->move({ (float)(1 * (1 / 2.0) * speed), (float)(-1 * (sqrt(3) / 2) * speed) });
					disTraveled += speed;
					faceRight = false;
					curAction = FLY_LEFT;
					ticks = 6;
				}
				else
				{
					//moves along hypotenuse of length speed, 30,60,90 right triangle
					sprite->move({ (float)(-1 * (1 / 2.0) * speed), (float)(-1 * (sqrt(3) / 2) * speed) });
					disTraveled += speed;
				}
			}
		}
		else if (faceRight)
		{
			sprite->move({ speed,0.0f });
			disTraveled += speed;
		}
		else
		{
			sprite->move({ -1.f*speed,0.0f });
			disTraveled += speed;
		}
	}
	else
	{
		if (faceRight)
		{
			sprite->move({ 3.f * speed,0.0f });
		}
		else
		{
			sprite->move({ -3.f * speed,0.0f });
		}
	}

	if (sprite->getPosition().x + sprite->getGlobalBounds().size.x < viewport->getCenter().x - 125.f)
	{
		if (viewportLoop)
			viewportLoop = false;
		else
		{
			set_active = false;
			set_visible = false;
		}
	}
	if (sprite->getPosition().x > viewport->getCenter().x + 125.f)
	{
		if (viewportLoop)
			viewportLoop = false;
		else
		{
			set_active = false;
			set_visible = false;
		}
	}
	//sf::FloatRect bounds = sprite->getLocalBounds();
	//sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
}


void Kirikiri::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = sprite->getPosition();
}