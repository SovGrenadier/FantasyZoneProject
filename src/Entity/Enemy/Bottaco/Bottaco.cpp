#include "Bottaco.h"


Bottaco::Bottaco(sf::Vector2f position) : Enemy()
{
	ticks = 13;
	//pos = { 840.f, 75.f };
	pos = position;

	sf::IntRect zone({ 10, 55}, { 63, 20});
	Animation* fly = new Animation(1, 3, zone);

	curAction = FLY_RIGHT;
	animations[curAction] = fly;

	sprite->setTexture(*texture);
	sprite->setPosition(pos);

	amplitudeX = 120.f;
	amplitudeY = 80.f;
	time = 0.f;
	centerX = pos.x;
	centerY = pos.y;
}


Bottaco::~Bottaco()
{
}


void Bottaco::spawn()
{
	//Two different formations
	/*
	1st Formation:
	one enemy enters from both side of ths screen,
	they come towards the middle following the
	figure 8 shape, then go off screen
	2nd Formation:
	a column of 4 enemy appears from one side of the screen
	follow the same movement
	*/
}


void Bottaco::move()
{
	//moves like a figure 8/infinity symbol
	//parametric equations

	float sine = static_cast<float>(sin(time));
	float cosine = static_cast<float>(cos(time));

	pos.x = centerX + amplitudeX * sine;
	pos.y = centerY + amplitudeY * sine * cosine;

	time += 0.05;
	sprite->setPosition(pos);
	
}


void Bottaco::update(int input)
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
	}
}


void Bottaco::death()
{
	alive = false;
	deathPos = pos;
}