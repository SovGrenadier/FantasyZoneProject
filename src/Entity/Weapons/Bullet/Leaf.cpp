#include "Leaf.h"
#include <iostream>
#include <time.h>

Leaf::Leaf(sf::Vector2f mouthPos) : Bullet(sf::Vector2f(0.f, 0.f), false)
{
	//366,391  8,7
	srand(time(NULL));
	rand();
	speed = -5.f;

	set_visible = true;
	set_active = true;
	alive = true;
	position = mouthPos;
	
	if (!texture->loadFromFile("../res/Levels/Round 1 wrapped with spawner locs.png"))
		std::cout << "Fail loading Round 1 wrapped with spawner locs.png\n";
	
	sprite = new sf::Sprite(*texture);

	sf::IntRect zone({ 366, 391 }, { 8, 7 });
	sprite->setTexture(*texture);
	sprite->setTextureRect(zone);
	sprite->setPosition(position);
	ownWeapon = false; 
}

Leaf::~Leaf()
{
	delete texture;
	delete sprite;
}