#include <SFML/Graphics.hpp>
#include<string>
#include "../Entity/Player/Player.h"

class Game {
public:
	Game();
	~Game();
	void run();
	int tick; 
private:
	sf::RenderWindow window;
	sf::Texture background1;
	sf::Sprite* backgroundSprite1;
	sf::View viewport;
	//Weapons weapon;

	//Player player;


};