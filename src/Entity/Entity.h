#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Animation/Animation.h"

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity();
	virtual ~Entity();
	
	void takeDamage(int); 
	
	//getter methods
	//std::vector<Entity*>* getEntities() { return &entities; }
	std::vector<std::shared_ptr<Entity>>* getEntities() { return &entities; }
	sf::Sprite* getSprite() { return sprite; }
	int getDamage() { return damage;}
	bool getVisible() { return set_visible; }
	bool getActive() { return set_active; }

	void getView(sf::View* view);
	//bools
	bool alive = true;
	bool ownWeapon = false;

	//abstract methods
	virtual void update(int input) = 0;
	virtual void death() = 0;
	void initialize(); 

	int ticks = 0;
protected:
	int health=1;
	sf::Vector2f pos, velocity;
	sf::Sprite* sprite;
	sf::Texture* texture;
	int damage = 1; 
	bool set_visible; //if false, the entity does not show on screen
	bool set_active; //if false, the entity does not update
	static sf::View* viewport;

private:
	//static std::vector<Entity*> entities;
	static std::vector<std::shared_ptr<Entity>> entities;
	
};