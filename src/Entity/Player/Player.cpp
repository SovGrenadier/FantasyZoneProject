#include"Player.h"

Player::Player()
{
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	Animation* rightFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{9,37},sf::Vector2i{45,49} });
	animations[GLIDE_RIGHT] = *rightFly;


}

Player::~Player()
{
	delete texture;
	delete sprite;
}


void Player::update(int input)
{
	//a is pressed
	if (((input % 0b00000100) / 0b00000010) == 1)
		faceRight = false;
	//w is pressed
	if (((input % 0b00010000) / 0b00001000) == 1)
		faceRight = true;
	switch (input)
	{
	case 0b00000000:
		if (faceRight)
			curAction = GLIDE_RIGHT;
		else
			curAction = GLIDE_LEFT;
		break;
	}



}

void Player::updateView()
{


}