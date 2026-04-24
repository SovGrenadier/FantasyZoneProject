#pragma once
#include "../Entity.h"
#include <SFML/Graphics.hpp>
#include <vector>


class Shop : public Entity
{
public:
	Shop();
	~Shop();
	void update(int input) override;
	void death() override;
	std::vector <sf::Sprite*> getSprites();
	sf::Sprite* getSprite() override { return ballonSprite; }
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
	sf::Sprite* ballonSprite;
	sf::Sprite* cursorSprite; 
	sf::Sprite* shopSprite;
	sf::Sprite* exitSprite;
	bool usedThisLevel;
};