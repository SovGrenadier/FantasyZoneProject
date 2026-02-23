#pragma once
#include "../Enemy.h"
#include "../../../Animation/Animation.h"


class Snake : public Enemy
{
public:
	Snake(bool isFacingRight);
	~Snake();

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