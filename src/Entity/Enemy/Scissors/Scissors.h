#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"



class Scissors : public Enemy
{
public:
	Scissors(sf::Vector2f pos, sf::View*);
	~Scissors();

	enum Actions
	{
		FLY_RIGHT,
		FLY_LEFT
	};

	enum Formation
	{
		VERTICAL,
		HORIZONTAL

		/*
		vertical is when there is a 1x3 formation of enemies
		near the bottom and near the top of the screen.

		horizontal is when near the middle of the screen there 
		is a 2x3 formation of enemies, like a rectangle
		*/
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
	float speed, acceleration;
	sf::Clock timer;
};