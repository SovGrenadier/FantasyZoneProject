#include<../../src/Entity/Entity.h>

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