#include "Entity.h"
#include <iostream>
std::vector<Entity*> Entity::entities;

Entity::Entity()
{
	entities.push_back(this);

	//temporary values
	health = 1;
	pos = sf::Vector2f(500.f, 600.f);
	set_visible = true;
	set_active = true;
	sprite = nullptr;
	texture = nullptr;
}

Entity::~Entity()
{
	//delete texture;
	//delete sprite;
} 


void Entity::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
		alive = false;
}
 void Entity::death()
{
	 set_visible = false;
	 set_active = false;
}
