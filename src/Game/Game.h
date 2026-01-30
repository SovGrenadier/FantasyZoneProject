#include <SFML/Graphics.hpp>
#include<string>

class Game {
public:
	Game();
	~Game();
	void run();

private:
	sf::RenderWindow window;
	sf::Texture background1;
	sf::Sprite* backgroundSprite1;
	sf::View viewport;



};