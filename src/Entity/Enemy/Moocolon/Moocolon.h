#pragma once
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"

//orange guy
//made up of groups that are together in a column but move in sync
class Moocolon : public Enemy
{
public:
	Moocolon(bool isFaceRight);
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
	float speed, amplitude, frequency,time, baseY; 
};