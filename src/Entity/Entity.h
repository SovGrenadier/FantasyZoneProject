#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Entity
{
public:
	Entity();
	~Entity();
	std::vector<Entity*>* getEntities() { return &entities; }
	sf::Sprite* getSprite() { return sprite; }
	virtual void update(int input) = 0;
	virtual void death() = 0;
	
protected:
	int health;
	sf::Vector2f pos, velocity;
	sf::Sprite* sprite;
	sf::Texture* texture;
	unsigned int ticks = 0;
	bool set_visible; //if false, the entity does not show on screen and has no collision

private:
	static std::vector<Entity*> entities;
};