#include "Spawner.h"

Spawner::Spawner()
{
	health = 20;
}

Spawner::~Spawner() {}

void Spawner::update_health(int tick)
{
	if (health <= 0)
	{
		death();
	}
}

void Spawner::spawn_enemy(int tick)
{
	if (tick % spawn_rate == 0 && set_active == true) //every 300 frames, spawn an enemy
	{
		spawn(position);
	}
}