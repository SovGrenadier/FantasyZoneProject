#include <SFML/Graphics.hpp>
#include "../Entity/Entity.h"

class Weapons : public Entity
{
public: 
	Weapons(); 
	~Weapons();
	void update() override;

private: 
	int damage;
	sf::Vector2f velocity; 
};