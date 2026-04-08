#pragma once
#include "Bullet.h"

class Leaf : public Bullet
{
public:
	Leaf(sf::Vector2f); //takes position of boss' mouth
	~Leaf();
	void update(int) override; 
	bool onScreen(); 

private:
	sf::Vector2f direction;
	sf::Vector2f position;
	float speedX, speedY; 
	Animation* fly;
};

