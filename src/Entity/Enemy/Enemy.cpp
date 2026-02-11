#include "Enemy.h"
#include <iostream>


Enemy::Enemy() : Entity()
{
	defeatPoints = 100;


	//if NOT loaded
	if (!(texture->loadFromFile("../res/Enemies.png")))
		std::cout << "FAILLLL\n";
	else
		std::cout << "Successful\n";
	//allocate memory for sprite, then set texture and position
	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);
	sprite->setPosition(pos);


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


void Enemy::spawn()
{
	//spawn logic
}


/*void Enemy::update()
{


}*/

void Enemy::update(int input)
{

}