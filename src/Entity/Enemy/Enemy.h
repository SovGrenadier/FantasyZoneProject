#include <SFML/Graphics.hpp>
#include <../../src/Entity/Entity.h>


class Enemy : public Entity 
{
public:
	Enemy();
	~Enemy();

	//takes position of enemy and determines if it is on screen
	//if returns false, (offscreen), despawn/death
	bool isOnScreen(sf::View &viewport);
	
	virtual void attack();

	void spawn();
	void update(int input) override;

	//void update() overide;

	sf::Sprite* getSprite();
private:
	unsigned int defeatPoints;

};