#pragma once
#include <unordered_map>
#include "../Enemy.h"
#include "../../../Animation/Animation.h"


class Kirikiri : public Enemy
{
public:
	Kirikiri(bool isFaceRight);
	~Kirikiri();

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

};