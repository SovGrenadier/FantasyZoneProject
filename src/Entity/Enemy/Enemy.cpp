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
		std::cout << "Fail loading Enemies.png\n";
	sprite = new sf::Sprite(*texture);

	//add 4 death frames
	deathFrames.push_back(sf::IntRect({ 11,419 }, { 8,8 }));
	deathFrames.push_back(sf::IntRect({ 21,417 }, { 12,12 }));
	deathFrames.push_back(sf::IntRect({ 35,415 }, { 16,16 }));
	deathFrames.push_back(sf::IntRect({ 11,419 }, { 8,8 }));


	tickRate = 12;
}


Enemy::~Enemy()
{
	delete texture;
	delete sprite;
}


bool Enemy::isOnScreen(sf::View &viewport)
{
	//get dimensions of viewport
	sf::Vector2f center = viewport.getCenter();
	sf::Vector2f size = viewport.getSize();

	center.x = center.x - size.x * 0.5f;
	center.y = center.y - size.y * 0.5f;
	
	//make rectangle of viewport
	sf::FloatRect viewBox(center, size);
	
	
	//check if enemy's position is on screen
	if (viewBox.findIntersection(sprite->getGlobalBounds()))
		return true;
	else
		return false;
}


void Enemy::attack()
{
	//attack logic
}


void Enemy::spawn(sf::Vector2f spawnpos)
{
	pos = spawnpos;
	set_active = true;
	set_visible = true;
}


void Enemy::move()
{
	pos += velocity;
	sprite->setPosition(pos);

	
}


void Enemy::update(int input)
{
	move();
	ticks += 1;
	if (!(spawnerCount >= 5))
	{
		addSpawner();
	}
}


void Enemy::death()
{
	set_visible = false;
	set_active = false;
}

void Enemy::addSpawner()
{
	Spawner* spawner = new Spawner();
	spawnerCount++;
}