#include "Snake.h"


Snake::Snake(sf::Vector2f position) : Enemy()
{
	float viewportCenterX = viewport->getCenter().x;
	if (position.x < viewportCenterX)
		faceRight = true;
	else
		faceRight = false;

	alive = true;
	ticks = 13;
	pos = position;
	speed = .6f;
	distTraveled = 0.0f;
	acceleration = 1.02f;

	//flying animation
	sf::IntRect zoneRight({ 9, 76 }, { 78, 15 });
	flyRight = new Animation(1, 3, zoneRight);

	sf::IntRect zoneLeft({ 104,78 }, { 78, 15 });
	flyLeft = new Animation(1, 3, zoneLeft);

	deathAnim = new Animation();
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

	sprite->setTexture(*texture);
	sprite->setTextureRect(*(animations[curAction])->getFrame(0));
	sprite->setPosition(pos);

}


Snake::~Snake()
{
	delete flyRight;
	delete flyLeft;
	delete deathAnim;
	flyLeft = nullptr;
	flyRight = nullptr;
	deathAnim = nullptr;
}


void Snake::move()
{
	//After 7 seconds, speed increases by 5% every tick
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		//handled through player
		//viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
	}

	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;

	distTraveled += speed;

	if (distTraveled > 200.f)
		speed *= acceleration;

	sprite->setPosition(pos);
}


void Snake::update(int input)
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


void Snake::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = pos;
}