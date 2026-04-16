#pragma once
#include "../Weapons.h"


class Bullet : public Weapons
{
public:
	Bullet(sf::Vector2f, bool, bool);
	~Bullet();
	void update(int input) override; 
	void death() override;
	bool slowBullets;
protected:
	float speed; 
	float viewPos;
};