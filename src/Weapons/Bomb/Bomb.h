#pragma once
#include "../Weapons.h"


class Bomb : public Weapons
{
public:
	Bomb(sf::Vector2f);
	~Bomb();
	void death() override;
	void update(int input) override;	
};
