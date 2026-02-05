#pragma once
#include <vector>
#include "../Entity.h"

class Spawner
{
public:
	Spawner();
	~Spawner();

	int spawnRate; //calculated in frames
	int health = 20; 

};
