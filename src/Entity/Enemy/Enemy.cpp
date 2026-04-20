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


/*bool Enemy::isOnScreen(sf::View& viewport)
{
	//get dimensions of viewport
	sf::Vector2f center = viewport.getCenter();
	sf::Vector2f size = viewport.getSize();

	center.x = center.x - size.x * 0.5f;
	center.y = center.y - size.y * 0.5f;
	
	//give leeway a little bit off screen
	float padding = 125.f;

	sf::Vector2f expandedPos;
	expandedPos.x = center.x - padding;
	expandedPos.y = center.y;

	sf::Vector2f expandedSize({size.x + padding * 2.f, size.y});

	//make rectangle of viewport
	sf::FloatRect viewBox(expandedPos, expandedSize);
	
	return viewBox.findIntersection(sprite->getGlobalBounds()).has_value();
}*/


void Enemy::attack()
{
	//attack logic
}


void Enemy::update(int input)
{
	ticks += 1;
}