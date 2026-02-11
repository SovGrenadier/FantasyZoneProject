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
	//void death();
	
protected:
	int health;
	sf::Vector2f pos;
	sf::Sprite* sprite;
	sf::Texture* texture;
	unsigned int ticks = 0;

private:
	static std::vector<Entity*> entities;
};