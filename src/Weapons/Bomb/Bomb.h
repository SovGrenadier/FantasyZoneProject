#pragma once
#include "../Weapons.h"


class Bomb : public Weapons
{
public:
	Bomb();
	~Bomb();
private:
	//can only travel vertically
	float velocity;

};
