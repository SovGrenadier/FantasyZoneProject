#include "Spawner.h"
#include "../Enemy/Kirikiri/Kirikiri.h"

Spawner::Spawner() : Enemy()
{
	health = 20;

	sf::IntRect zone({ 8, 20 }, { 51, 15 });
	Animation* fly = new Animation(1, 3, zone);

	sprite->setTexture(*texture);
	sprite->setPosition(pos);
}

Spawner::~Spawner() {}

void Spawner::updateHealth(int tick)
{
	if (health <= 0)
	{
		death();
	}
}

void Spawner::spawnEnemy(int tick)
{
	Kirikiri kirikiri = Kirikiri(true);
	if (tick % spawn_rate == 0 && set_active == true) //every 300 frames, spawn an enemy
	{
		kirikiri.spawn(pos);
	}
}

void Spawner::update()
{
	updateHealth(ticks);
	spawnEnemy(ticks);
}