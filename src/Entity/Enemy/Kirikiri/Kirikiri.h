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
		FLY_LEFT,
		DEATH
	};
	void move() override;
	void update(int) override;
	void death() override;

	sf::Sprite* getSprite() { return sprite; }
	std::unordered_map<Actions, Animation*> animations;
private:
	Animation* flyRight;
	Animation* flyLeft;
	Animation* deathAnim;
	Actions curAction;
	bool faceRight;
	//this will be used to determine when kirikiri should fly off the screen
	float disTraveled = 0.0f;
	//used for switch direction animation
	float disTravelTemp = 0.0f;
	float speed;//speed will be equivalent to the viewport speed when the kirikiri is created
	float viewPos;
	sf::Vector2f spawnPos;
	//when player hits the edge of the viewport and we want to switch movement to the right
	bool switchRight;
	//when player hits the edge of the viewport and we want to switch movement to the left
	bool switchLeft;
};