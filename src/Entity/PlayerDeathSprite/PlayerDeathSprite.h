#pragma once
#include"../Entity.h"

class PlayerDeath : public Entity
{
public:
	//this class will take in angle in degrees
	PlayerDeath(sf::Vector2f pos, float speed, float angle);
	~PlayerDeath();
	void update(int input) override;
	void death() override;

private:
	int maxTicks = 400;
	float speed;
	float angle;//in degrees
};