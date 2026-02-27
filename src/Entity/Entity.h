#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Animation/Animation.h"

class Entity
{
public:
	Entity();
	~Entity();
	std::vector<Entity*>* getEntities() { return &entities; }
	sf::Sprite* getSprite() { return sprite; }
	virtual void update(int input) = 0;
	virtual void death() = 0;
	bool ownWeapon = false;
	void setPosition(sf::Vector2f);
	void takeDamage(int); 
	int getDamage() { return damage;}
	bool alive = true;

protected:
	int health=1;
	sf::Vector2f pos, velocity;
	sf::Sprite* sprite;
	sf::Texture* texture;
	unsigned int ticks = 0;
	bool set_visible;//if false, the entity does not show on screen and has no collision
	int damage = 1; 

private:
	static std::vector<Entity*> entities;
	
};