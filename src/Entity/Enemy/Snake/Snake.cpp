#include "Snake.h"


Snake::Snake(sf::Vector2f position) : Enemy()
{
	float viewportCenterX = viewport->getCenter().x;
	if (position.x < viewportCenterX)
		faceRight = true;
	else
		faceRight = false;

	alive = true;
	timer.restart();
	ticks = 13;
	//pos = { 840.f, 120.f };
	pos = position;
	speed = .6f;
	acceleration = 1.05f;

	//flying animation
	sf::IntRect zoneRight({ 9, 76 }, { 78, 15 });
	Animation* flyRight = new Animation(1, 3, zoneRight);

	sf::IntRect zoneLeft({ 104,78 }, { 78, 15 });
	Animation* flyLeft = new Animation(1, 3, zoneLeft);

	Animation* deathAnim = new Animation();
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

	sprite->setPosition(pos);
}


void Snake::update(int input)
{
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