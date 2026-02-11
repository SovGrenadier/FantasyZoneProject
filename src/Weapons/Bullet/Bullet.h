#pragma once
#include "../Weapons.h"


class Bullet : public Weapons
{
public:
	Bullet();
	~Bullet();
private:
	//can only travel vertically
	float velocity;
};