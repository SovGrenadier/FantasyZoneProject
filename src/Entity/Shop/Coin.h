#pragma once
#include "../../src/Entity/Entity.h"

class Coin : public Entity
{
public:
	Coin(sf::Vector2f, int);
	~Coin(); 
	void update(int) override; 
	void death() override; 
	void move(); 
	int getValue() { return value; }; 

private: 
	int zone; 
	std::vector<sf::IntRect> zones; 
	int ticks = 0, value; 
	float initialHeight, yMax, ySpeed; 
	float ground; 
	bool bounce, changeMax;
	void animation(); 
	bool fullView; 
};

