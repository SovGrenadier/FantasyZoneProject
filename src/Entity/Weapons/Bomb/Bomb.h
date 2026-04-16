#pragma once
#include "../Weapons.h"


class Bomb : public Weapons
{
public:
	Bomb(sf::Vector2f, bool); 
	~Bomb();
	void death() override;
	void update(int input) override;
private:
	//true means the bomb was launched in the right direction,
	// false means the bomb was launched in the left direction
	bool direction;
	sf::FloatRect ground;
	sf::Vector2f viewStart;
	sf::Vector2f start;
	float height;
	float xPos, yPos, viewMov;
};
