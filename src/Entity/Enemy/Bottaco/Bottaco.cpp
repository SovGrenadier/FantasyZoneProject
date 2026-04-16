#include "Bottaco.h"


Bottaco::Bottaco(sf::Vector2f position) : Enemy()
{
	ticks = 13;
	pos = position;

	Animation* fly = new Animation(1, 3, sf::IntRect({ 10,55 }, { 63,20 }));

	Animation* deathAnim = new Animation();
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));
	deathAnim->addFrame(sf::IntRect({ 21,417 }, { 12,12 }));
	deathAnim->addFrame(sf::IntRect({ 35,415 }, { 16,16 }));
	deathAnim->addFrame(sf::IntRect({ 11,419 }, { 8,8 }));

	animations[FLY] = fly;
	animations[DEATH] = deathAnim;

	curAction = FLY;

	sprite->setTexture(*texture);
	sprite->setTextureRect(*animations[curAction]->getFrame(0));
	sprite->setPosition(pos);

	amplitudeX = 80.f;
	amplitudeY = 40.f;
	time = 0.f;
	centerX = pos.x;
	centerY = pos.y;
	std::cout << "Bottaco created\n";
}


Bottaco::~Bottaco()
{
	std::cout << "Bottaco destroyed\n";
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

	time += 0.015;
	sprite->setPosition(pos);
}


void Bottaco::update(int input)
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
	move();
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
		sf::FloatRect bounds = sprite->getLocalBounds();
		sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	}
}


void Bottaco::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = pos;
}