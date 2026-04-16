#pragma once
#include <vector>
#include <unordered_map>
#include<memory>
#include "../Enemy/Enemy.h"
#include"../Player/Player.h"

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
	void setHeath(int newHealth) { health = newHealth; }
	int getHeath() { return health; }
	void update(int input) override;
	void death();
	void getPlayer(std::shared_ptr<Player> newPlayer) { player = newPlayer; }
	sf::Vector2f position;
	sf::Sprite* getSprite() override;
	int spawnerDist;
private:
	Actions curAction;
	int spawn_rate = 5 * 60; //5 seconds between each spawn sequence, 60 fps

	sf::Sprite* deathSprite;
	sf::Texture* deathTexture;

	//Inheriting from enemy causes problems so we just steal it instead
	unsigned int curDeathFrame; 
	std::vector <sf::IntRect> deathFrames;
	std::unordered_map<Actions, Animation*> animations;
	unsigned int tickRate;
	sf::Vector2f deathPos;
	static inline std::shared_ptr<Player> player = std::make_shared<Player>();
};
