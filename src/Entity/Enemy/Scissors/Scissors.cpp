#include "Scissors.h"


Scissors::Scissors(bool isFaceRight) : Enemy()
{
	timer.restart();
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 60.f };
	acceleration = 1.05f;


	sf::IntRect zone({ 9, 4 }, { 80, 16 });
	Animation* fly = new Animation(1,4,zone);

	if (faceRight)
		curAction = FLY_RIGHT;
	else
		curAction = FLY_LEFT;

	animations[curAction] = fly;

	//needed for movement
	speed = .5f;
	amplitude = 10.f;
	frequency = 1.f;
	time = 0.f;
	baseY = pos.y;

	sprite->setTexture(*texture);
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
	ticks++;
	move();

	if (faceRight)
	{
		//flip sprite so its facing right
		sprite->setScale({ 1.f,1.f });
	}
	else
	{
		//flip sprite so its facing left
		sprite->setScale({ -1.f,1.f });
	}
	if (ticks >= tickRate)
	{
		ticks = 0;
		sprite->setTextureRect(*animations[curAction]->nextFrame());
	}

	sprite->setPosition(pos);
}


void Scissors::death()
{

}