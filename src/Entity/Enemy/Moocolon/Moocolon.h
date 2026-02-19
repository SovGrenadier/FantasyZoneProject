#pragma once
#include "../Enemy.h"
#include "../../../Animation/Animation.h"
#include <unordered_map>

//orange guy
//made up of groups that are together in a column but move in sync
class Moocolon : public Enemy
{
public:
	Moocolon();
	~Moocolon();

	enum Actions
	{
		FLY_RIGHT,
		FLY_LEFT
	};

	void spawn() override;
	void move() override;
	void update(int) override;
	void death() override;

	sf::Sprite* getSprite() { return sprite; }
	std::unordered_map<Actions, Animation*> animations;
private:
	Actions curAction;
	bool faceRight;
	float speed;
	float amplitude;
	float frequency;
	float time;
	float baseY;
};