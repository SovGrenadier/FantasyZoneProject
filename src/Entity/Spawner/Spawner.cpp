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
		spawn();
	}
}

void Spawner::update_health(int tick)
{
	//check_collision(Entity);
	if (health <= 0)
	{
		//death();
	}
}

void Spawner::update(int input)
{

}