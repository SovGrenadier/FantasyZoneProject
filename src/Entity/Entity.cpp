#include "Entity.h"
std::vector<Entity*> Entity::entities;

Entity::Entity()
{
	entities.push_back(this);

	//temporary values
	health = 1;
	pos = sf::Vector2f(500.f, 600.f);
	set_visible = true;
	sprite = nullptr;
	texture = nullptr;
}

Entity::~Entity()
{
	
} 


