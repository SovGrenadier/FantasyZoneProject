#pragma once
#include <iostream>
#include <SFML/System/Clock.hpp>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"


class Snake : public Enemy
{
public:
	Snake(sf::Vector2f pos);
	~Snake();

	enum Actions
	{
		FLY_RIGHT,
		FLY_LEFT,
		DEATH
	};


	void move() override;
	void update(int) override;
	void death() override;

	sf::Sprite* getSprite() { return sprite; }
	std::unordered_map<Actions, Animation*> animations;
private:
	Actions curAction;
	bool faceRight;
	float speed, acceleration, distTraveled;
};