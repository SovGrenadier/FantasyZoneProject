#pragma once
#include "../Entity.h"


class Shop : public Entity
{
public:
	Shop();
	~Shop();
	void update(int input) override;
	void death() override;

	enum State
	{
		NOT_ACTIVE,
		FLYING, //after 2000 dollars, spawn and fly around
		BUY_PHASE,
		PARTS_SELECT
	};
private:
	State curState;
	sf::Vector2f cursorPos;
	sf::Sprite* cursorSprite; 
	sf::Sprite* shopSprite;
	sf::Sprite* exitSprite;
	bool usedThisLevel;
};