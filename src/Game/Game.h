#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include"../Entity/Entity.h"
#include "../Entity/Player/Player.h"
#include"../Entity/Weapons/Bullet/Bullet.h"
#include"../Entity/Weapons/Bomb/Bomb.h"
#include "../Entity/Enemy/Bottaco/Bottaco.h"
#include "../Entity/Enemy/Moocolon/Moocolon.h"
#include "../Entity/Enemy/Snake/Snake.h"
#include "../Entity/Enemy/Scissors/Scissors.h"
#include "../Entity/Enemy/Kirikiri/Kirikiri.h"
#include "../Entity/Spawner/Spawner.h"
#include "../Entity/Shop/Shop.h"
#include "../Entity/Weapons/Bullet/Leaf.h"

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

	std::shared_ptr<Player> player = std::make_shared<Player>(); 

	//Player player;
	/*this binary int will represent input
	* The first bit will represent if w is pressed
	* The second bit will represent if a is pressed
	* The third bit will represent if s is pressed
	* The fourth bit will represent if d is pressed
	* the fifth bit will represent if x is pressed
	* the sixth bit will represent if z is pressed
	* */
	int input = 0b00000000;
	//we need to deallocate bullets and bombs from this vector 
	//std::vector<Entity*>* entities;
	std::vector<std::shared_ptr<Entity>>* entities;
	void updateEntities();
	void drawEntities();
	void checkCollision();
	void initialize(); 
	sf::Vector2f pos = sf::Vector2f(345.f, 290.f);//player position + offset

	/*Snake* snakeDummy = new Snake(true);
	Snake* snakeDummy2 = new Snake(false);
	Scissors* scissorsDummy = new Scissors(true);
	Moocolon* moocolonDummy = new Moocolon(true);
	Kirikiri* kiriDummy = new Kirikiri(true, pos);
	Bottaco* bottacoDummy = new Bottaco;
	Spawner* spawnerDummy = new Spawner(0);
	Spawner* spawnerDummy2 = new Spawner(1);
	Spawner* spawnerDummy3 = new Spawner(2);
	Spawner* spawnerDummy4 = new Spawner(3);
	Spawner* spawnerDummy5 = new Spawner(4);*/ 

	std::shared_ptr<Snake> snakeDummy = std::make_shared<Snake>(true);
	std::shared_ptr<Snake> snakeDummy2 = std::make_shared<Snake>(false); 
	std::shared_ptr<Scissors> scissorsDummy = std::make_shared<Scissors>(true); 
	std::shared_ptr<Moocolon> moocolonDummy = std::make_shared<Moocolon>(true);
	std::shared_ptr<Kirikiri> kiriDummy = std::make_shared<Kirikiri>(true, pos);
	std::shared_ptr<Bottaco> bottacoDummy = std::make_shared<Bottaco>(); 
	std::shared_ptr<Spawner> spawnerDummy = std::make_shared<Spawner>(0); 
	std::shared_ptr<Spawner> spawnerDummy2 = std::make_shared<Spawner>(1);
	std::shared_ptr<Spawner> spawnerDummy3 = std::make_shared<Spawner>(2);
	std::shared_ptr<Spawner> spawnerDummy4 = std::make_shared<Spawner>(3);
	std::shared_ptr<Spawner> spawnerDummy5 = std::make_shared<Spawner>(4);





	
	Leaf* leafDummy;
	//Shop* shop = new Shop();
};