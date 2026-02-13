#include "Bullet.h"


Bullet::Bullet(sf::Vector2f playPos) : Weapons(playPos)
{ 
	velocity= sf::Vector2f(1.0f, 0.f);
}


Bullet::~Bullet()
{
}


void Bullet::death()
{
	//death logic
}