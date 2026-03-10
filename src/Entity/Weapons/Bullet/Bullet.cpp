#include "Bullet.h"


Bullet::Bullet(sf::Vector2f playPos, bool faceRight) : Weapons(playPos)
{

	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{12,26},sf::Vector2i{7,9}});

	if (faceRight)
	{
		speed = 7.5f;
	}
	else
	{
		speed = -7.5f;
	}
}


Bullet::~Bullet()
{
}


void Bullet::death()
{
	
}

void Bullet::update(int input)
{
	sprite->move({ speed, 0 });
}

