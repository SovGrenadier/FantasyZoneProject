#include "../Shop/Shop.h"
#include <iostream>

Shop::Shop()
{
	//appears on screen after two destroyed spawners
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Shop.png"))
		std::cout << "Fail loading Shop.png\n";
	sprite = new sf::Sprite(*texture);

}


Shop::~Shop()
{

}


void Shop::update(int input)
{

}