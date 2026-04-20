#pragma once
#include"../Entity.h"

class PlayerDeath : public Entity
{
public:
	PlayerDeath(float speed, float angle);
	~PlayerDeath();
	void update(int input) override;
	void death() override;

private:
	int maxTicks = 400;
	float speed;
	float angle;
};