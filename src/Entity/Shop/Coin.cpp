#include "Coin.h"
#include <iostream>

Coin::Coin(sf::Vector2f pos)
{
	texture = new sf::Texture();

	if (!texture->loadFromFile("../res/Shop Transparent.png"))
		std::cout << "\nCoin: Error Loading from File\n";
	//sprite->setTexture(*texture); 
	sprite = new sf::Sprite(*texture);
	zone = sf::IntRect(sf::Vector2i{ 444, 186 }, sf::Vector2i{ 21,13 });
	sprite->setTextureRect(zone); 
}

Coin::~Coin()
{

}


void Coin::update(int input)
{

}


void Coin::death()
{

}