#pragma once 
#include <SFML/Graphics.hpp>
#include "../Entity.h"
#include "../../Animation/Animation.h"

class Weapons : public Entity
{
public: 
	Weapons(sf::Vector2f);
	~Weapons();
	void update(int input) override;

protected: 
	int damage; 
};