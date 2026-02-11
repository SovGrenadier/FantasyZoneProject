#include "Entity.h"
std::vector<Entity*> Entity::entities;

Entity::Entity()
{
	//temporary value
	health = 1;
	entities.push_back(this);
	pos = sf::Vector2f(500.f, 600.f);
}

Entity::~Entity()
{
	texture = nullptr; 
} 


/*
void Entity::death()
{

}
*/