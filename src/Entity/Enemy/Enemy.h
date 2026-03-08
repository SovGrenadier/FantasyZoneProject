#pragma once
#include <SFML/Graphics.hpp>
#include "../../src/Entity/Entity.h"
#include "../../Animation/Animation.h"


class Enemy : public Entity 
{
public:
	Enemy();
	~Enemy();

	//takes position of enemy and determines if it is on screen
	//if returns false, (offscreen), despawn/death
	bool isOnScreen(sf::View &viewport);

	virtual void attack();
	virtual void spawn(sf::Vector2f);
	virtual void move();
	
	//inherited methods
	void update(int input) override;
	void death() override;

	//methods for spawner counting
	int spawnerCount = 0;
	void addSpawner();

	//get methods
	sf::Sprite* getSprite();
protected:
	std::vector <sf::IntRect> deathFrames;
	unsigned int tickRate;
	unsigned int curDeathFrame;
	unsigned int defeatPoints;
	sf::Vector2f deathPos;
};