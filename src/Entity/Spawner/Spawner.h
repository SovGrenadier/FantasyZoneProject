#pragma once
#include <vector>
#include "../Enemy/Enemy.h"

class Spawner : public Enemy
{
public:
	Spawner(int);
	~Spawner();
	/*
	spawner 1 pos 800, 25

	*/

    void spawnEnemy(int);
	void updateHealth(int); //runs every tick, checks for damage
	void update();
	sf::Vector2f position{ 800.f, 32.f };

private:
	int spawn_rate = 5 * 60; //5 seconds between each spawn sequence, 60 fps
};
