#include "Bullet.h"


Bullet::Bullet(sf::Vector2f playPos, bool faceRight) : Weapons(playPos)
{

	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{12,22},sf::Vector2i{8,16}});

	if (faceRight)
	{
		speed = 1.5f;
	}
	else
	{
		speed = -1.5f;
	}
}


Bullet::~Bullet()
{
}


void Bullet::death()
{
	//death logic
}

void Bullet::update(int input)
{
	sprite->move({ speed, 0 });
}