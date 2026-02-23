#pragma once
#include "../Enemy.h"


class Scissors : public Enemy
{
public:
	Scissors(bool isFaceRight);
	~Scissors();

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