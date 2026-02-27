#pragma once
#include <vector>
#include "../Enemy/Enemy.h"

class Spawner : public Enemy
{
public:
	Spawner();
	~Spawner();

	void spawn_enemy(int);
	void update_health(int); //runs every tick, checks for damage

	sf::Vector2f position{ 100.f, 100.f };

private:
	int spawn_rate = 5 * 60; //5 seconds between each spawn sequence, 60 fps
};
