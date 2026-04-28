#include "Entity.h"
#include <iostream>

std::vector<std::shared_ptr<Entity>> Entity::entities;
sf::View* Entity::viewport;


Entity::Entity()
{
	//temporary values
	health = 1;
	pos = sf::Vector2f(500.f, 600.f);
	set_visible = true;
	set_active = true;
	sprite = nullptr;
	texture = nullptr;

	initialized = false; 
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
		death();
}


void Entity::getView(sf::View* view) 
{ 
	viewport = view;
}


void Entity::initialize()
{
	if (!initialized)
	{
		entities.push_back(shared_from_this());
		initialized = true; 
	}
}


bool Entity::isOnScreen(sf::View &viewport)
{
	//get dimensions of viewport
	sf::Vector2f center = viewport.getCenter();
	sf::Vector2f size = viewport.getSize();

	center.x = center.x - size.x * 0.5f;
	center.y = center.y - size.y * 0.5f;

	//give leeway a little bit off screen
	float padding = 125.f;

	sf::Vector2f expandedPos;
	expandedPos.x = center.x - padding;
	expandedPos.y = center.y;

	sf::Vector2f expandedSize({ size.x + padding * 2.f, size.y });

	//make rectangle of viewport
	sf::FloatRect viewBox(expandedPos, expandedSize);

	return viewBox.findIntersection(sprite->getGlobalBounds()).has_value();
}