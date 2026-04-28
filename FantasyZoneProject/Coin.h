#pragma once
#include "../../src/Entity/Entity.h"

class Coin : public Entity
{
public:
	Coin(sf::Vector2f);
	~Coin(); 
	void update(int) override; 
	void death() override; 

private: 
	sf::IntRect zone; 

};

