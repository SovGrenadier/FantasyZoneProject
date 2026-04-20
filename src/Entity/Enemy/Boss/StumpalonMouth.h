#pragma once
#include "../../src/Entity/Enemy/Enemy.h"
//#include "../src/Entity/Enemy/Boss/Boss.h"
class StumpalonMouth : public Enemy
{
public:
	StumpalonMouth(sf::Vector2f);
	~StumpalonMouth(); 
	void setVisibility(bool); 
	void changeState(); 
	void update(int) override; 
	void attack() override {}; 
	void move() override; 
	void death() override; 
	void takeDamage(int) override; 
	int getHealth() { return health; };


private:
	sf::IntRect zone; 
	Animation* changeColor; 
	int ticks, frame; 
	const double PI = 4.0 * std::atan(1.0);
};

