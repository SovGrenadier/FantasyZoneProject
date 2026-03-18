#pragma once
#include "../src/Entity/Weapons/Bullet/Bullet.h"

class Leaf : public Bullet
{
public:
	Leaf(sf::Vector2f); //takes position of boss' mouth
	~Leaf();

private:
	sf::Vector2f direction;
	sf::Vector2f position;
};

