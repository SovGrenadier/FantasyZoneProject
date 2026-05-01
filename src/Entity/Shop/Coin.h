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
	int ticks = 0, value, time; 
	float initialHeight, yMax, ySpeed, initialheight; 
	float ground; 
	bool bounce, changeMax;
	bool fullView, firstBounce = true;
	double width;
	double maxY(int);
	float parabola(int);
};

