#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "../Entity/Player/Player.h"
#include"../Entity/Weapons/Bullet/Bullet.h"
#include"../Entity/Weapons/Bomb/Bomb.h"

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
	Player player;
	/*this binary int will represent input
	* The first bit will represent if w is pressed
	* The second bit will represent if a is pressed
	* The third bit will represent if s is pressed
	* The fourth bit will represent if d is pressed
	* the fifth bit will represent if x is pressed
	* */
	int input = 0b00000000;
	std::vector<Entity*>* entities;
	void updateEntities();
	void drawEntities();
	sf::Vector2f pos = sf::Vector2f(345.f, 290.f);//player position + offset

};