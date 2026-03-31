#pragma once
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"


class Kirikiri : public Enemy
{
public:
	Kirikiri(bool isFaceRight, sf::Vector2f newPos);
	~Kirikiri();

	enum Actions
	{
		FLY_RIGHT,
		FLY_LEFT
	};
	void move() override;
	void update(int) override;
	void death() override;

	sf::Sprite* getSprite() { return sprite; }
	std::unordered_map<Actions, Animation*> animations;
private:
	Actions curAction;
	bool faceRight;
	sf::Vector2f speed;
	float disTraveled = 0.0f;
	//this will be used to determine when kirikiri should fly off the screen
	sf::Vector2f spawnPos;
};