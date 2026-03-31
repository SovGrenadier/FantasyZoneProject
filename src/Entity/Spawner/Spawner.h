#pragma once
#include <vector>
#include "../Enemy/Enemy.h"

class Spawner : public Entity
{
public:
	Spawner(int);
	~Spawner();
	/*
	spawner 1 pos 800, 25

	*/

    void spawnEnemy(int);
	void updateHealth(int); //runs every tick, checks for damage
	void update(int input) override;
	void death();
	sf::Vector2f position;

private:
	int spawn_rate = 5 * 60; //5 seconds between each spawn sequence, 60 fps
	int spawnerDist;

	sf::Sprite* deathSprite;
	sf::Texture* deathTexture;

	//Inheriting from enemy causes problems so we just steal it instead
	unsigned int curDeathFrame; 
	std::vector <sf::IntRect> deathFrames;
	unsigned int tickRate;
	sf::Vector2f deathPos;
};
