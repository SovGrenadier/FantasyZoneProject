#include "Enemy.h"
#include "../Spawner/Spawner.h"
#include <iostream>


Enemy::Enemy() : Entity()
{
	curDeathFrame = 0;
	//loads enemies png, child class will have to crop
	defeatPoints = 100;
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Enemies.png"))
		std::cerr << "Fail loading Enemies.png\n";
	sprite = new sf::Sprite(*texture);

	set_active = true;
	set_visible = true;

	tickRate = 12;
}


Enemy::~Enemy()
{
	delete texture;
	delete sprite;
}


void Enemy::attack()
{
	//attack logic
}


void Enemy::update(int input)
{
	ticks += 1;
}