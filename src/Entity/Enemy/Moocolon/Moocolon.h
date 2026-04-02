#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"

//orange guy
//made up of groups that are together in a column but move in sync
class Moocolon : public Enemy
{
public:
	Moocolon(sf::Vector2f pos, sf::View* viewport);
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
	Actions curAction;
	bool faceRight;
	float amplitude, centerY, time;
	float speed;
	sf::Clock timer;
	bool bounce, bounceTwice;
	unsigned int bounceIndex, bounceCount;
	float previousY;

};