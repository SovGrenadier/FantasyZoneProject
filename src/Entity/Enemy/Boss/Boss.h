#include "../Enemy.h"
#include "../../src/Entity/Weapons/Bullet/Leaf.h"
#include "../../StumpalonMouth.h"
#pragma once

class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	void attack() override;
	void death() override;
	void move() override; 
	void update(int) override;

	enum IntRect
	{
		OPEN_MOUTH,
		CLOSED_MOUTH
	};

private:
	int ticks; 
	Animation* glideRight; 
	int attacks = 0; 
	int frame = 0; 
	const double PI = 4.0 * std::atan(1.0); 
	bool mouthOpen; 
	std::shared_ptr<StumpalonMouth> mouth; 
};