#pragma once
#include <SFML/System/Clock.hpp>
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"


class Moocolon : public Enemy
{
public:
	Moocolon(sf::Vector2f pos);
	~Moocolon();

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
	sf::Vector2f getPosition() { return pos; }
private:
	Animation* flyLeft;
	Animation* flyRight;
	Animation* deathAnim;
	Actions curAction;
	bool faceRight;
	float amplitude, centerY, time;
	float speed, acceleration;
	float previousY, distTraveled;
	bool bouncing;
	unsigned int bounceIndex, bounceCount;

};