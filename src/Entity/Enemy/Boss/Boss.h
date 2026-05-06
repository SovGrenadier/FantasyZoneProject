#include "../Enemy.h"
#include "../../src/Entity/Weapons/Bullet/Leaf.h"
#include "../../src/Entity/Enemy/Boss/StumpalonMouth.h"
#pragma once

class Boss : public Enemy
{
public:
	Boss(float);
	~Boss();

	void attack() override;
	void death() override;
	void move() override; 
	void update(int) override;
	int getHealth();
	// used to determine which frame the current sprite is at and change the frame
	enum state { OPEN_MOUTH = 2,  AJAR_MOUTH = 1, CLOSED_MOUTH = 0};

private:
	int ticks; 
	Animation* glideRight; 
	int frame = 0; 
	const double PI = 4.0 * std::atan(1.0); // for movement calculations
	std::shared_ptr<StumpalonMouth> mouth; 
	bool openning = true; 
};
