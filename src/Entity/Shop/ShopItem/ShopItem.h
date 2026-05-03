#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ShopItem
{
public:
	enum ItemType {
		BigWings, 
		TurboEngine, 
		LaserBeam, 
		SevenWayShot,
		FireBomb,
		HeavyBomb,
		JetEngine,
		RocketEngine,
		WideBeam,
		TwinBombs,
		SmartBomb,
		ExtraShip
	};
public:
	ShopItem(sf::Vector2f, sf::Vector2f, int, ItemType);
	~ShopItem();

	void setBought(bool condition) { bought = condition; }
	sf::FloatRect getBox() { return boundary; }
	sf::Sprite* getSoldSprite();
	bool getBoughtStatus() { return bought; }
	int getValue() { return value; }
	void moveSprite(sf::Vector2f);
	std::string getItemTitle();
	ItemType getType() { return type; }
private:
	ItemType type;
	sf::FloatRect boundary;
	sf::Texture* itemTexture;
	sf::Sprite* soldOutSprite;
	sf::Sprite* emptySprite;
	sf::Vector2f soldOutPosition;
	bool bought;
	int value;
};

