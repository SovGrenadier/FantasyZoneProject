#include "../Enemy.h"
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

private:
	int ticks; 
	Animation* glideRight; 
	std::shared_ptr<StumpalonMouth> mouth; 
};