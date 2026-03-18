#include "Spawner.h"
#include "../Enemy/Kirikiri/Kirikiri.h"
#include <iostream>

Spawner::Spawner(int spawnerCount)
{
	std::cout << "Test";
	health = 20;
	sf::Vector2f spawnerLocs[5] = { { 800.f, 32.f },{ 1011.f, 60.f },{ 1094.f, 120.f },{ 1281.f,50.f },{ 471.f, 102.f } };
	position = spawnerLocs[spawnerCount];

	set_visible = true;
	set_active = true;
	alive = true;

	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Levels/Round 1 wrapped with spawner locs.png"))
		std::cout << "Fail loading Round 1 wrapped with spawner locs.png\n";
	sprite = new sf::Sprite(*texture);

	sf::IntRect zone({ 75, 406 }, { 48, 25 });
	sprite->setTexture(*texture);
	sprite->setTextureRect(zone);
	sprite->setPosition(position);

	std::cout << "Spawner created at " << position.x << ", " << position.y << "\n";
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
	Kirikiri* kirikiri = new Kirikiri(true, position);
	if (tick % spawn_rate == 0 && set_active == true) //every 300 frames, spawn an enemy
	{
		kirikiri->spawn(position);
	}
}

void Spawner::update(int input)
{
	updateHealth(ticks);
	spawnEnemy(ticks);
}

void Spawner::death()
{
	set_active = false;
}