#pragma once
#include <vector>
#include <unordered_map>
#include "../Enemy/Enemy.h"

class Spawner : public Entity
{
public:
	Spawner(int);
	~Spawner();
	/*
	spawner 1 pos 800, 25

	*/

	enum Actions
	{
		ACTIVEFLY, // if in the air
		ACTIVEGROUND, // if on the wall/ground
		DEATH
	};

    void spawnEnemy(int);
	void updateHealth(int); //runs every tick, checks for damage
	void update(int input) override;
	void death();
	sf::Vector2f position;

private:
	Actions curAction;
	int spawn_rate = 5 * 60; //5 seconds between each spawn sequence, 60 fps
	int spawnerDist;


	//Inheriting from enemy causes problems so we just steal it instead
	unsigned int curDeathFrame; 
	std::vector <sf::IntRect> deathFrames;
	std::unordered_map<Actions, Animation*> animations;
	unsigned int tickRate;
	sf::Vector2f deathPos;
};
