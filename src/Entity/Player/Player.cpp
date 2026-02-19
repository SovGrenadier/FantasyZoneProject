#include"Player.h"

Player::Player()
{
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	Animation* rightFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{9,37},sf::Vector2i{36,12} });
	animations[GLIDE_RIGHT] = rightFly;
	sprite->setPosition(sf::Vector2f{ 790.f,109.f });
	tickRate = 100000;
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
			sprite->move({0.40f,0.0f});
			viewport->move({ 0.40f,0.0f });
		}
		else
		{
			curAction = GLIDE_LEFT;
			sprite->move({ -0.40f,0.0f });
		}
		tickRate = 12;
		break;
	case 0b00000001:
		break;
	case 0b00000010:
		break;
	case 0b00000100:
		break;
	case 0b00001000:
		faceRight = true;
		curAction = MOVE_RIGHT;
		break;

	}
	updateView(input);
	if (ticks == tickRate)
	{
		//reset to 0 so ticks doesn't get to large
		ticks = 0;
		sprite->setTextureRect(*(animations[curAction]->nextFrame()));
	}


}

void Player::updateView(int input)
{
	std::cout << sprite->getPosition().x << std::endl;
	//viewport goes of left end
	if ((viewport->getCenter().x - 125) > 32.f&& (viewport->getCenter().x - 125) < 34.f)
	{
		viewport->setCenter({ 1049.f+((viewport->getCenter().x - 125)-33.f) + 125.f,101.5f});
		sprite->setPosition({ sprite->getPosition().x+1049.f-33.f,sprite->getPosition().y });
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1108.f && (viewport->getCenter().x - 125) < 1110.f)
	{
		std::cout << "test" << std::endl;
		viewport->setCenter({ 93.f + ((viewport->getCenter().x + 125) - 1109.f) + 125.f,101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
	}


	if (input == 0b00010000)
	{
		shoot();
	}

	switch (input)
	{
	case 0b00000000:
		if (faceRight)
		{
			//viewport->move({ 0.40f,0.0f });
		}
		else
		{
			//viewport->move({ -0.40f,0.0f });
		}
		break;
	case 0b00000001:
		break;
	case 0b00000010:
		break;
	case 0b00000100:
		break;
	case 0b00001000:
		break;

	}

}


void Player::death()
{

}


void Player::shoot()
{
	Bullet x(pos);
}

void Player::bomb()
{

}