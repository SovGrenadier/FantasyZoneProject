#pragma once
#include <SFML/System/Clock.hpp>
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"


class Scissors : public Enemy
{
public:
	Scissors(sf::Vector2f pos);
	~Scissors();

	enum Actions
	{
		FLY_RIGHT,
		FLY_LEFT,
		DEATH
	};

	void spawn();
	void move() override;
	void update(int) override;
	void death() override;

	sf::Sprite* getSprite() { return sprite; }
	std::unordered_map<Actions, Animation*> animations;
private:
	Actions curAction;
	bool faceRight;
	float amplitude, time, baseY;
	float speed, acceleration, distTraveled;
};