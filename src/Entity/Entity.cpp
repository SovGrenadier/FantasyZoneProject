#include "Entity.h"
std::vector<Entity*> Entity::entities;

Entity::Entity()
{
	//temporary value
	health = 1;
	entities.push_back(this);
	//allocate memory for texture
	texture = new sf::Texture;
	pos = sf::Vector2f(500.f, 600.f);
}

Entity::~Entity()
{
	//deallocate
	delete texture;
	texture = nullptr; 
} 


void Entity::update()
{

}

/*
void Entity::death()
{

}
*/