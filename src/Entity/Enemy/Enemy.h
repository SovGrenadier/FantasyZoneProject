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
	virtual void move() = 0;
	
	//inherited methods
	void update(int input) override;
	virtual void death() = 0;

	//get methods
	sf::Sprite* getSprite();
protected:
	std::vector <sf::IntRect> deathFrames;
	unsigned int tickRate;
	unsigned int curDeathFrame;
	unsigned int defeatPoints;
	int spawnerCount = 0;
	sf::Vector2f deathPos;
};