#include "Leaf.h"
#include <iostream>
#include <time.h>


/// <summary>
/// Creates a leaf object, assigns it a random velcoity, and initializes its position
/// </summary> 
/// <param name = "mouthPos"></param> 
Leaf::Leaf(sf::Vector2f mouthPos) : Weapons(mouthPos)
{
	texture = new sf::Texture(); 
	speedX = -(rand() % 4 + .5); 
	speedY = rand() % 4 - 2.5; 

	set_visible = true;
	set_active = true;
	alive = true;
	damage = 1; 
	
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


/// <summary> 
/// Deallocates memory used by sprites, textures, and animations 
/// </summary>
Leaf::~Leaf()
{
	delete texture;
	delete sprite;
}


/// <summary> 
/// Moves the leafs, ensures they are looped with the viewport, and deactivates the lead once 
/// certain conditions are met
/// </summary> 
/// <param name = "input"></param> 
void Leaf::update(int input)
{
	//Ensures sprite doesn't disappear when the viewport loops
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	
	ticks++; 

	//Animate the leads 
	if(ticks%8 == 0)
		sprite->setTextureRect(*fly->nextFrame());

	sprite->move(sf::Vector2f{ speedX, speedY });


	//remove the leafs if they are offscreen or if they have no health 
	if (!isOnScreen(*viewport))
	{
		set_active = false; 
		set_visible = false; 
	}
	else if (health == 0)
	{
		set_active = false; 
		set_visible = false; 
	}
}
