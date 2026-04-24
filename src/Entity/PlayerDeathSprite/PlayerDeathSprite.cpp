#include"PlayerDeathSprite.h"
#include<cmath>

PlayerDeath::PlayerDeath(sf::Vector2f pos, float newSpeed, float newAngle)
{
	set_active = true;
	set_visible = true;
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	speed = newSpeed;
	angle = newAngle;
	angle = (angle / 360.f) * 2 * 3.14159265359;
	sprite->setTextureRect(sf::IntRect{ sf::Vector2i{81,39},sf::Vector2i{8,8} });
	sprite->setPosition(pos);

}

PlayerDeath::~PlayerDeath()
{
	delete texture;
	delete sprite;
}

void PlayerDeath::update(int input)
{
	sprite->move({ std::cos(angle)*speed,std::sin(angle) * speed });
	speed *= 0.99;
}

void PlayerDeath::death()
{

}