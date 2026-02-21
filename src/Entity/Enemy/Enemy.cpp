#include "Enemy.h"
#include <iostream>


Enemy::Enemy() : Entity()
{
	//loads enemies png, child class will have to crop
	defeatPoints = 100;
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Enemies.png"))
		std::cout << "Fail loading enemies.png\n";
	sprite = new sf::Sprite(*texture);

	tickRate = 12;
}


Enemy::~Enemy()
{
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


void Enemy::spawn()
{
	//spawn logic
}


void Enemy::move()
{
	pos += velocity;
	sprite->setPosition(pos);

	
}


void Enemy::update(int input)
{
	ticks++;
	move();

}


void Enemy::death()
{
	set_visible = false;
}