#pragma once
#include "../Weapons.h"


class Bomb : public Weapons
{
public:
	Bomb(sf::Vector2f,bool);
	~Bomb();
	void death() override;
	void update(int input) override;
private:
	//true means the bomb was launched in the right direction,
	// false means the bomd was launched in the left direction
	bool direction;
};
