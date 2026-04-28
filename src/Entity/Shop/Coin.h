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
	sf::IntRect zone; 
	int ticks = 0, value; 
	float initialHeight, yMax; 
	float ground; 
	bool bounce, changeMax; 
};

