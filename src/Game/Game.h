#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "../Entity/Player/Player.h"
#include"../Entity/Weapons/Bullet/Bullet.h"
#include"../Entity/Weapons/Bomb/Bomb.h"
#include "../Entity/Enemy/Bottaco/Bottaco.h"
#include "../Entity/Enemy/Moocolon/Moocolon.h"
#include "../Entity/Enemy/Snake/Snake.h"
#include "../Entity/Enemy/Scissors/Scissors.h"
#include "../Entity/Enemy/Kirikiri/Kirikiri.h"
#include "../Entity/Spawner/Spawner.h"


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
	
	Snake* dummy1 = new Snake(true);
	Scissors* dummy2 = new Scissors(true);
	Moocolon* dummy3 = new Moocolon(true);
	//Kirikiri* dummy4 = new Kirikiri(true);
	Bottaco* dummy5 = new Bottaco(true);
	Spawner* spawner1 = new Spawner();
};