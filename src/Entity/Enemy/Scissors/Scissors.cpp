#include "Scissors.h"


Scissors::Scissors(sf::Vector2f position) : Enemy()
{
	float viewportCenterX = viewport->getCenter().x;
	if (position.x < viewportCenterX)
		faceRight = true;
	else
		faceRight = false;

	timer.restart();
	ticks = 13;
	//pos = { 840.f, 60.f };
	pos = position;
	acceleration = 1.05f;

	sf::IntRect zoneRight({ 9, 4 }, { 80, 16 });
	Animation* flyRight = new Animation(1, 4, zoneRight);

	sf::IntRect zoneLeft({ 103,6 }, { 80,16 });
	Animation* flyLeft = new Animation(1, 4, zoneLeft);

	Animation* deathAnim = new Animation;
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

	//needed for movement
	speed = .6f;
	amplitude = 10.f;
	time = 0.f;
	baseY = pos.y;

	sprite->setTexture(*texture);
	sprite->setTextureRect(*(animations[curAction]->getFrame(0)));
	sprite->setPosition(pos);
}


Scissors::~Scissors()
{
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
}


void Scissors::spawn()
{

}


void Scissors::move()
{
	/*
	* horizontal movement is based off speed
	* vertical movement is changed via a sine func
	* After 7 seconds, vertical movement stops
	* and horizontal movement increases by 5% every tick
	*/

	float wave = static_cast<float>(sin(time));

	sf::Time lifeSpan = sf::seconds(7.f);
	bool isAlive = true;
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
		//std::cout << "test" << std::endl;
		//viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
	}
	if (timer.getElapsedTime() >= lifeSpan)
	{
		isAlive = false;
		speed *= acceleration;
	}
	if (faceRight && isAlive)
	{
		pos.x += speed;
		pos.y = baseY + amplitude * wave;
	}
	else if (!faceRight && isAlive)
	{
		pos.x -= speed;
		pos.y = baseY + amplitude * wave;
	}
	else if (faceRight && !isAlive)
		pos.x += speed;
	else if (!faceRight && !isAlive)
		pos.x -= speed;


	time += 0.05f;
	sprite->setPosition(pos);
}


void Scissors::update(int input)
{
	if (!isOnScreen(*viewport))
	{
		set_active = false;
		set_visible = false;
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
				//setOrigin
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


void Scissors::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = pos;
}