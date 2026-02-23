#include "Spawner.h"

Spawner::Spawner()
{
	health = 20;
}

Spawner::~Spawner() {}

void Spawner::update_health(int tick)
{
	//check_collision(Entity);
	if (health <= 0)
	{
		//death();
	}
}

void Spawner::update(int input, int tick)
{
	if (tick % spawn_rate == 0 && set_visible == true) //every 300 frames, spawn an enemy
	{
		spawn();
	}
}