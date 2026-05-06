#include "Bullet.h"
#include <iostream>


/// <summary>
/// Creates a bullet, initailizes its position to the player's, and determines the velocity.
/// </summary>
/// <param name = "playerPos"></param>
/// <param name = "faceRight"></param>
/// <param name = "slowBullets"></param>
Bullet::Bullet(sf::Vector2f playPos, bool faceRight, bool slowBullets) : Weapons(playPos)
{
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Opa-Opa.png"))
		std::cout << "Error Loading Image";

	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);

	sprite->setPosition(playPos);
	damage = 1;
	ownWeapon = true;

	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{12,26},sf::Vector2i{7,9} });


	if (slowBullets)
		speed = 2.f;
	else
		speed = 7.5f;

	if (!faceRight)
		speed *= -1; 

	viewPos = viewport->getCenter().x;
}


/// <summary>
/// deallocates all memory used for sprites and textures.
/// </summary>
Bullet::~Bullet()
{
	delete sprite;
	delete texture;
}


/// <summary>
/// Changes the state of the bullet once it's deactivated
/// </summary>
void Bullet::death()
{
	set_active = false;
	set_visible = false;
	alive = false;
}


/// <summary>
/// Moves the bullet and deactivates it once certain conditions are met. 
/// </summary> 
/// <param name = "input"></param> 
void Bullet::update(int input)
{
	if (health <= 0)
		death();
	else if (!isOnScreen(*viewport))
		death();

	sprite->move({ speed+(viewport->getCenter().x-viewPos), 0});
	//Move sprite and ensure movement works if a bullet is shot at the edge
	//of the viewport (need to move the viewport to the other end)

	if (sprite->getPosition().x > (viewport->getCenter().x + 130.f))
	{
		set_active = false;
		set_visible = false;
	}
	if (sprite->getPosition().x < (viewport->getCenter().x - 130.f))
	{
		set_active = false;
		set_visible = false;
	}
	viewPos = viewport->getCenter().x;
}

