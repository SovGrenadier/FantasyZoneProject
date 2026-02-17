#pragma once
#include "../Weapons.h"


class Bullet : public Weapons
{
public:
	Bullet(sf::Vector2f);
	~Bullet();
	void update(int input) override; 
	void death() override;

private:

};