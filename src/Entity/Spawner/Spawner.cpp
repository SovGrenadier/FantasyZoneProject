#include "Spawner.h"

Spawner::Spawner()
{
	health = 20;
}

Spawner::~Spawner() {}

const void Spawner::spawn_enemy(int tick)
{
	if (tick % spawn_rate == 0) //every 300 frames
	{
		//spawning logic
	}
}

void Spawner::update_health(int tick)
{
	//checkCollision(Entity);
	if (health <= 0)
	{
		death();
	}
}