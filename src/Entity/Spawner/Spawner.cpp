#include "Spawner.h"
#include "../Enemy/Kirikiri/Kirikiri.h"
#include <iostream>

Spawner::Spawner() : Enemy()
{
	health = 20;
	sf::Vector2f spawnerLocs[5] = { { 800, 25 },{ 800, 150 },{ 800, 275 },{ 800, 400 },{ 800, 500 } };
	position = spawnerLocs[spawnerCount];

	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Levels/Round 1 wrapped with spawner locs.png"))
		std::cout << "Fail loading Enemies.png\n";
	sprite = new sf::Sprite(*texture);

	sf::IntRect zone({ 135, 365 }, { 182, 389 });

	sprite->setTexture(*texture);
	sprite->setPosition(position);

	std::cout << "Spawner created at " << position.x << ", " << position.y << "\n";
	addSpawner();
}

Spawner::~Spawner() 
{
	delete texture;
	delete sprite;
}

void Spawner::updateHealth(int tick)
{
	if (health <= 0)
	{
		death();
	}
}

void Spawner::spawnEnemy(int tick)
{
	Kirikiri kirikiri = new Kirikiri(true);
	if (tick % spawn_rate == 0 && set_active == true) //every 300 frames, spawn an enemy
	{
		kirikiri.spawn(position);
	}
}

void Spawner::update()
{
	updateHealth(ticks);
	spawnEnemy(ticks);
}