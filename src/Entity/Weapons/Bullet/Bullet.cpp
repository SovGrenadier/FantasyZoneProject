#include "Bullet.h"
#include <iostream>


Bullet::Bullet(sf::Vector2f playPos, bool faceRight) : Weapons(playPos)
{
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error Loading Image";
	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);
	sprite->setPosition(playPos);
	damage = 1;
	ownWeapon = true;

	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{12,26},sf::Vector2i{7,9}});

	if (faceRight)
	{
		speed = 7.5f;
	}
	else
	{
		speed = -7.5f;
	}
	viewPos = viewport->getCenter().x;
}


Bullet::~Bullet()
{
}


void Bullet::death()
{
	
}

void Bullet::update(int input)
{
	if (health <= 0)
	{
		set_active = false;
		set_visible = false;
		alive = false;
	}
	sprite->move({ speed+(viewport->getCenter().x-viewPos), 0});
	//Move sprite and ensure movement works if a bullet is shot at the edge
	//of the viewport (need to move the viewport to the other end)

	if (sprite->getPosition().x > (viewport->getCenter().x + 130.f))
		set_active = false;
	if (sprite->getPosition().x < (viewport->getCenter().x - 130.f))
		set_active = false;
	viewPos = viewport->getCenter().x;
}

