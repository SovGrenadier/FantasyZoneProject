#include "Leaf.h"
#include <iostream>
#include <time.h>

Leaf::Leaf(sf::Vector2f mouthPos) : Weapons(mouthPos)
{
	texture = new sf::Texture(); 
	speedX = -(rand() % 4 + .5); 
	speedY = rand() % 4 - 2.5; 

	set_visible = true;
	set_active = true;
	alive = true;
	
	if (!texture->loadFromFile("../res/Levels/Round 1 wrapped with spawner locs.png"))
		std::cout << "Fail loading Round 1 wrapped with spawner locs.png\n";
	
	sprite = new sf::Sprite(*texture);

	sf::IntRect zone({ 366, 391 }, { 8, 7 });
	sprite->setTexture(*texture);
	sprite->setTextureRect(zone);
	sprite->setPosition(mouthPos);

	ownWeapon = false; 
	fly = new Animation(1, 3, sf::IntRect(sf::Vector2i{ 366, 391 }, sf::Vector2i{ 28,7 }));
}

Leaf::~Leaf()
{
	delete texture;
	delete sprite;
}

void Leaf::update(int input)
{
	ticks++; 
	if(ticks%8 == 0)
		sprite->setTextureRect(*fly->nextFrame());

	sprite->move(sf::Vector2f{ speedX, speedY });
}

bool Leaf::onScreen()
{
	return true; 
}