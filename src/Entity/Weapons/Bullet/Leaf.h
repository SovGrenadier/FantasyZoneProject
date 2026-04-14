#pragma once
#include "../Weapons.h"

class Leaf : public Weapons
{
public:
	Leaf(sf::Vector2f); //takes position of boss' mouth
	~Leaf();
	void update(int) override; 
	void death() override {}; 
	bool onScreen(); 

private:
	sf::Vector2f direction;
	sf::Vector2f position;
	float speedX, speedY; 
	Animation* fly;
};

