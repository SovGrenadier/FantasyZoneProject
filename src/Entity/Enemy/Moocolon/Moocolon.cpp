#include "Moocolon.h"
#include <iostream>
#include <cmath>

Moocolon::Moocolon() : Enemy()
{
	defeatPoints = 100;
	
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Enemies.png"))
		std::cout << "Fail loading Moocolon.\n";
	sprite = new sf::Sprite(*texture);
	
	sprite->setTextureRect(sf::IntRect({ 10,37 }, { 16,16 }));

	speed = 5.f;
	amplitude = 50.f;
	frequency = 3.f;
	time = 0.f;
	baseY = pos.y;
	
	sprite->setTexture(*texture);
	sprite->setPosition(pos);
}


Moocolon::~Moocolon()
{
	delete sprite;
	delete texture;
}


void Moocolon::spawn()
{
	/*two different ways to spawn
	1. a group of 4 will form a square and move that way
	2. a column of 4 will move horizontally
	*/

}


void Moocolon::move()
{
	//move like a sinusoidal function regardless of formation
	if (faceRight)
		pos.x += speed;
	else
		pos.x -= speed;
	
	time += 0.05f;

	float wave = static_cast<float>(sin(time));
	pos.y = baseY + amplitude * wave;

	sprite->setPosition(pos);
}


void Moocolon::update(int input)
{
	ticks++;
	move();

}


void Moocolon::death()
{
	set_visible = false;
}