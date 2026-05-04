#include "Moocolon.h"
#include <iostream>
#include <cmath>

Moocolon::Moocolon(sf::Vector2f position) : Enemy()
{
	float viewCenterX = viewport->getCenter().x;

	if (position.x < viewCenterX)
		faceRight = true;
	else
		faceRight = false;

	ticks = 13;
	pos = position;

	//frames
	sf::IntRect zone({ 10, 37 }, { 34, 17 });
	flyRight = new Animation(1, 2, zone);
	
	zone = sf::IntRect({ 148,39 }, { 34, 17});
	flyLeft = new Animation(1, 2, zone);

	deathAnim = new Animation;
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));
	deathAnim->addFrame(sf::IntRect({ 21,417 }, { 12,12 }));
	deathAnim->addFrame(sf::IntRect({ 35,415 }, { 16,16 }));
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));

	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;
	animations[FLY_RIGHT] = flyRight;
	animations[FLY_LEFT] = flyLeft;
	animations[DEATH] = deathAnim;


	centerY = pos.y;
	speed = 0.6f;
	acceleration = 1.02f;
	amplitude = 17.5f;
	time = 0.f;
	bounceIndex = 1;
	previousY = pos.y;
	distTraveled = 0.f;
	bouncing = true;
	bounceCount = 0;

	sprite->setTexture(*texture);
	sprite->setTextureRect(*(animations[curAction]->nextFrame()));
	sprite->setPosition(pos);
	
}


Moocolon::~Moocolon()
{
	delete flyLeft;
	delete flyRight;
	delete deathAnim;
	flyLeft = nullptr;
	flyRight = nullptr;
	deathAnim = nullptr;
}


void Moocolon::spawn()
{
}

//to-do: fix not moving at all after reaching centerY
void Moocolon::move()
{
	if (faceRight)
		pos.x += speed;
	else if (!faceRight)
		pos.x -= speed;


	float wave = centerY + amplitude * static_cast<float>(sin(time));
	bool decreasing = previousY < wave;
	bool inRange = (previousY < centerY + .5f) && (previousY > centerY - .5f);

	if (bouncing)
	{
		if (decreasing && inRange)
		{
			bounceIndex++;
			if (bounceIndex % 2 == 0)
			{
				time *= -1.f;
				wave = centerY + amplitude * static_cast<float>(sin(time));
				bounceCount++;
			}

			if (bounceCount >= 2)
				bouncing = false;
		}

		pos.y = wave;


	}
	else
		distTraveled += speed;

	if (distTraveled > 30.f)
		speed *= acceleration;
	if (time == 0.f)
		if (faceRight)
			time += 0.05f;
		else
			time -= 0.05f;
	else if (time > 0.f)
		time += 0.05f;
	else if (time < 0.f)
		time -= 0.05f;
	sprite->setPosition(pos);
	previousY = pos.y;
}


void Moocolon::update(int input)
{
	//Ensures sprite doesn't disappear when the viewport loops
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	if (!isOnScreen(*viewport))
	{
		if (viewportLoop)
			viewportLoop = false;
		else
		{
			set_active = false;
			set_visible = false;
		}
		return;
	}
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
				sprite->setTextureRect(*animations[DEATH]->nextFrame());
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
	else
	{
		move();

		if (ticks >= tickRate)
		{
			ticks = 0;
			sprite->setTextureRect(*animations[curAction]->nextFrame());
			sf::FloatRect bounds = sprite->getLocalBounds();
			sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
		}
		sprite->setPosition(pos);
	}
}


void Moocolon::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = pos;
}