#include<SFML/Graphics.hpp>
#include<vector>

class Entity
{
public:
	Entity();
	~Entity();
	std::vector<Entity*>* getEntities() { return &entities; }
	//virtual void update();
	//void death();
	sf::Sprite* getSprite() { return sprite; }

protected:
	int health;
	sf::Vector2f pos;
	sf::Sprite* sprite;
	sf::Texture* texture;

private:
	static std::vector<Entity*> entities;
};