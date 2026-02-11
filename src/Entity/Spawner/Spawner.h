#pragma once
#include <vector>
#include "../Enemy/Enemy.h"

class Spawner : public Enemy
{
public:
	Spawner();
	~Spawner();

	const void spawn_enemy(int);
	void update_health(int); //runs every tick, checks for damage

private:
	int spawn_rate = 5 * 60; //5 seconds between each spawn sequence, 60 fps
};
