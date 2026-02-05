#include "Enemy.h"


Enemy::Enemy() : Entity()
{
	defeatPoints = 100;
	texture->loadFromFile("../res/Enemies.png");
	sprite = new sf::Sprite(*texture);

}


Enemy::~Enemy()
{

}


bool Enemy::isOnScreen(sf::View &viewport)
{
	//get rectangle of what is on screen
	sf::FloatRect viewPos = viewport.getViewport();
	
	//check if hitbox is on screen
	if (viewPos.contains(this->pos))
		return true;
	else
		return false;
}


void Enemy::attack()
{

}


void Enemy::spawn()
{

}


/*void Enemy::update()
{


}*/