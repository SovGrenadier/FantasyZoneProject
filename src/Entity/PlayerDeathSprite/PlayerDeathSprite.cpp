#include"PlayerDeathSprite.h"

PlayerDeath::PlayerDeath(float newSpeed, float newAngle)
{
	set_active = true;
	set_visible = true;
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	speed = newSpeed;
	angle = newAngle;
	//sprite->setTextureRect()

}

PlayerDeath::~PlayerDeath()
{
	delete texture;
	delete sprite;
}

void PlayerDeath::update(int input)
{

}

void PlayerDeath::death()
{

}