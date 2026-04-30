#pragma once
#include "../Entity.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>


class Shop : public Entity
{
public:
	enum State
	{
		NOT_ACTIVE,
		FLYING, //after 2000 dollars, spawn and fly around
		BUY_PHASE,
		PARTS_SELECT
	};
public:
	Shop();
	~Shop();

	void update(int input) override;
	void move();
	void death() {};
	void setState(State state) { curState = state; }
	void setSpritePositions();
	std::vector <sf::Sprite*> getSprites();
	sf::Sprite* getSprite() override;
	sf::RectangleShape getRect() { return temporary; }
	sf::RectangleShape getRect2() { return temporary2; }
	State getState() { return curState; }
private:
	void checkCollison();
	State curState;
	sf::RectangleShape topRect;
	sf::Vector2f spriteMov;
	sf::Sprite* ballonSprite;
	sf::Sprite* cursorSprite;
	sf::Sprite* shopSprite;
	sf::Sprite* exitSprite;
	float time, speed;
	float baseY, yTraveled, xTraveled;
	float frequency;
	sf::FloatRect leftBarrier, rightBarrier;
	sf::FloatRect roof, floor;
	sf::RectangleShape temporary;
	sf::RectangleShape temporary2;
	bool usedThisLevel, boughtItem;
};