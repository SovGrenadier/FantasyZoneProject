#include "Entity.h"
std::vector<Entity*> Entity::entities;

Entity::Entity()
{
	entities.push_back(this);
}

Entity::~Entity()
{

}

/*
void Entity::death()
{

}
*/