#include "Scissors.h"


/// Constructor of Scissors
/// shouldShiftHappens defines whether or not scissors will immediately
/// travel upwards, or travel downwards
Scissors::Scissors(sf::Vector2f position, bool shouldShiftHappen) : Enemy()
{
	sf::Vector2f viewportCenter = viewport->getCenter();
	if (position.x < viewportCenter.x)
		faceRight = true;
	else
		faceRight = false;

	if (shouldShiftHappen)
		shift = 3.14f;
	else
		shift = 0.f;


	ticks = 13;
	pos = position;
	acceleration = 1.02f;

	sf::IntRect zoneRight({ 9, 4 }, { 80, 16 });
	flyRight = new Animation(1, 4, zoneRight);

	sf::IntRect zoneLeft({ 103,6 }, { 80,16 });
	flyLeft = new Animation(1, 4, zoneLeft);

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

	//needed for movement
	speed = .6f;
	amplitude = 7.5f;
	time = 0.f;
	baseY = pos.y;
	distTraveled = 0.0f;

	sprite->setTexture(*texture);
	sprite->setTextureRect(*(animations[curAction]->getFrame(0)));
	sprite->setPosition(pos);

}

/// deconstructor
Scissors::~Scissors()
{
	delete flyLeft;
	delete flyRight;
	delete deathAnim;
	flyLeft = nullptr;
	flyRight = nullptr;
	deathAnim = nullptr;
}

// moves, which follows a sinusodial pattern
void Scissors::move()
{
	float wave = static_cast<float>(sin(time + shift));

	bool isAlive = true;
	if (distTraveled >= 200.f)
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
	
	if (!isAlive)
		speed *= acceleration;
	distTraveled += speed;
	time += 0.05f;
	sprite->setPosition(pos);
}

/// runs every frame, updates the position, animation, sprite
void Scissors::update(int input)
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

/// gets Scissors ready to run death animation
void Scissors::death()
{
	curAction = DEATH;
	alive = false;
	deathPos = pos;
}