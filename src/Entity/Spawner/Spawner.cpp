#include "Spawner.h"
#include "../Enemy/Kirikiri/Kirikiri.h"
#include <iostream>

Spawner::Spawner(int spawnerCount)
{
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
	
	//taken from Enemy
	curDeathFrame = 0;
	deathTexture = new sf::Texture();
	if (!deathTexture->loadFromFile("../res/Enemies.png"))
		std::cout << "Fail loading Enemies.png\n";
	deathSprite = new sf::Sprite(*deathTexture);

	deathFrames.push_back(sf::IntRect({ 11,419 }, { 8,8 }));
	deathFrames.push_back(sf::IntRect({ 21,417 }, { 12,12 }));
	deathFrames.push_back(sf::IntRect({ 35,415 }, { 16,16 }));
	deathFrames.push_back(sf::IntRect({ 11,419 }, { 8,8 }));
	//

	ticks = 1;
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
	spawnerDist = viewport->getCenter().x - position.x;
	//every 300 frames, spawn an enemy
	if (tick % spawn_rate == 0 && set_active == true &&
		125 >= spawnerDist && spawnerDist >= -125) 
	{
		ticks = 0;
		std::shared_ptr<Kirikiri> dummy = std::make_shared<Kirikiri>(true, position);
		dummy->initialize();
	}
	if(ticks<spawn_rate)
		ticks++;
}

void Spawner::update(int input)
{
	updateHealth(ticks);
	spawnEnemy(ticks);

	if (!alive)
	{
		if (ticks >= tickRate)
		{
			ticks = 0;

			if (curDeathFrame >= deathFrames.size())
			{
				set_active = false;
				set_visible = false;
			}

			else
			{
				//change sprite
				sprite->setTextureRect(deathFrames.at(curDeathFrame));
				//set origin
				sf::FloatRect bounds = sprite->getLocalBounds();
				sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
				//set position back regardless of change due to origin
				sprite->setPosition(deathPos);
				//advance to next death frame
				curDeathFrame++;
			}
		}
		return;
		//exit method so sprite doesn't get updated further
	}
}

void Spawner::death()
{
	set_active = false;
	alive = false;
	deathPos = pos;
}