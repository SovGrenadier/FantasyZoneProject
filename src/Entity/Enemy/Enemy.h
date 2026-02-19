#include <SFML/Graphics.hpp>
#include "../../src/Entity/Entity.h"
#include "../../Animation/Animation.h"


class Enemy : public Entity 
{
public:
	Enemy();
	~Enemy();

	//takes position of enemy and determines if it is on screen
	//if returns false, (offscreen), despawn/death
	bool isOnScreen(sf::View &viewport);
	
	virtual void attack();

	virtual void spawn();
	virtual void move();
	
	//inherited methods
	void update(int input) override;
	void death() override;
	
	//get methods
	sf::Sprite* getSprite();
protected:
	unsigned int tickRate;
	unsigned int defeatPoints;

};