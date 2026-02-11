#include"Player.h"

Player::Player()
{
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	Animation* rightFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{9,37},sf::Vector2i{36,12} });
	animations[GLIDE_RIGHT] = rightFly;
	sprite->setPosition({ 330.f,290.f });

}

Player::~Player()
{
	delete texture;
	delete sprite;
}


void Player::update(int input)
{
	ticks++;
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
		{
			curAction = GLIDE_RIGHT;
			//sprite->move({0.5f,0.0f});
		}
		else
		{
			curAction = GLIDE_LEFT;
			//sprite->move({ -0.5f,0.0f });
		}
		break;
	}
	if (ticks == 3)
	{
		//reset to 0 so ticks doesn't get to large
		ticks = 0;
		sprite->setTextureRect(*(animations[curAction]->nextFrame()));
	}


}

void Player::updateView()
{


}