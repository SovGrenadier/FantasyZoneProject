#include "Boss.h"
#include<iostream>


Boss::Boss()
{
	texture = new sf::Texture(); 
	if (!texture->loadFromFile("../res/Bosses.png"))
		std::cout << "Error Loaing from File"; 
	sprite = new sf::Sprite(*texture);

	sprite->setTextureRect(sf::IntRect{ sf::Vector2i(11,14), sf::Vector2i(62,79) });
	sprite->setPosition(sf::Vector2f(790.f, 109.f));
	sprite->setScale(sf::Vector2f(.5f, .5f)); 
}


Boss::~Boss()
{

}


void Boss::attack()
{

}


void Boss::death()
{
	//death logic
}

void Boss :: move()
{

}

void Boss::update(int input)
{

}