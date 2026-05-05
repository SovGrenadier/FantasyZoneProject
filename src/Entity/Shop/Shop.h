#pragma once
#include "../Entity.h"
#include "../Shop/ShopItem/ShopItem.h"
#include "../Weapons/Bomb/Bomb.h"
#include "../Weapons/Bullet/Bullet.h"
#include "../UI/UI.h"
#include "../Player/Player.h"
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
		FLYING,
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
	void setSpritePositions(int*, int*);
	std::vector <sf::Drawable*> getSprites();
	sf::Sprite* getSprite() override;
	sf::Vector2f getViewCenterOld() { return viewCenterOld; }
	sf::RectangleShape getRect() { return topRect; }
	sf::RectangleShape getRect2() { return temporary2; }
	State getState() { return curState; }
	bool canMoveShopItems(sf::Vector2f);
private:
	void moveShopItems(sf::Vector2f);
	void checkCollison();
	void checkShopPosition();
	void createShopItems();
	void applyEffects();
	State curState;
	sf::RectangleShape topRect;
	sf::Vector2f viewCenterOld;
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
	int* scorePtr;
	int* livesPtr;
	std::vector <ShopItem*> shopItems;
	std::vector <Bullet*> bulletTypes;
	std::vector <Bomb*> bombTypes;
	UI* exitUI;
};