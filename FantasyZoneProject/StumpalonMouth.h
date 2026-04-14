#pragma once
#include "../src/Entity/Enemy/Enemy.h"
class StumpalonMouth : public Enemy
{
public:
	StumpalonMouth(sf::Vector2f);
	~StumpalonMouth(); 
	void setVisibility(bool); 
	void changeState(); 
	void update(int) override; 
	void spawn(sf::Vector2f pos) override{}; 
	void attack() override {}; 
	void move() override; 
	void death() override {}; 
	void takeDamage(int) override; 


private:
	sf::IntRect zone; 
	Animation* changeColor; 
	int ticks, frame; 
	const double PI = 4.0 * std::atan(1.0);
};

