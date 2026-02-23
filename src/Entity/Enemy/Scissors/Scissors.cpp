#include "Scissors.h"


Scissors::Scissors(bool isFaceRight) : Enemy()
{
	//moves like sine func, then stops the sine movement
	// and charges straight
	faceRight = isFaceRight;
	ticks = 13;
	pos = { 840.f, 90.f };

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
	frequency = 0.1f;
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
	moves up and down like a sine func, then stops at 
	last point and charges straight
	*/
	
	
	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;

	time += 0.05f; 

	float wave = static_cast<float>(sin(time));
	pos.y = baseY + amplitude * wave;

	sprite->setPosition(pos);
}


void Scissors::update(int input)
{
	ticks++;
	//move();

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