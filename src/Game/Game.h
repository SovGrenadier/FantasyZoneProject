#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include<random>
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
#include "../Entity/Enemy/Boss/Boss.h"
#include "../Entity/UI/UI.h"
#include"../../FantasyZoneProject/Coin.h"
#pragma once

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
	sf::Texture backgroundStart;
	sf::Sprite* backgroundSpriteStart;
	sf::View viewport;
	sf::View viewportStart;

	std::shared_ptr<Player> player = std::make_shared<Player>(); 

	/*this binary int will represent input
	* The first bit will represent if w is pressed
	* The second bit will represent if a is pressed
	* The third bit will represent if s is pressed
	* The fourth bit will represent if d is pressed
	* the fifth bit will represent if x is pressed
	* the sixth bit will represent if z is pressed
	* */
	int input = 0b00000000;
	bool start = false;
	bool inShop = false;
	//we need to deallocate bullets and bombs from this vector 
	//std::vector<Entity*>* entities;
	std::vector<std::shared_ptr<Entity>>* entities;
	void updateEntities();
	void drawEntities();
	void checkCollision();
	void enemyWave();
	void handleMovementInput(const std::optional<sf::Event>&);
	static int getRandomInt(int min, int max);
	void initialize(); 
	int score;
	int highScore;
	bool invincible = false;
	bool shopSpawned = false;
	std::string UItext = "";
	std::string UItext2 = "";
	std::string UItext3 = "";
	std::string scoreStr = "";	
	std::string highScoreStr = "";
	std::string tempStr;
	void removeDead(); 
	void removeEnemies();
	void reset();
	bool activeBoss, loading; 
	sf::Vector2f pos = sf::Vector2f(345.f, 290.f);//player position + offset
	sf::Vector2f offset;
	sf::Vector2f offset2;
	// offset used for UI position
	//Temporary for testing 
	std::shared_ptr<Spawner> spawnerDummy = std::make_shared<Spawner>(0); 
	std::shared_ptr<Spawner> spawnerDummy2 = std::make_shared<Spawner>(1);
	std::shared_ptr<Spawner> spawnerDummy3 = std::make_shared<Spawner>(2);
	std::shared_ptr<Spawner> spawnerDummy4 = std::make_shared<Spawner>(3);
	std::shared_ptr<Spawner> spawnerDummy5 = std::make_shared<Spawner>(4);
	std::shared_ptr<Spawner> spawnerDummy6 = std::make_shared<Spawner>(5);
	std::shared_ptr<Spawner> spawnerDummy7 = std::make_shared<Spawner>(6);
	std::shared_ptr<Spawner> spawnerDummy8 = std::make_shared<Spawner>(7);
	std::shared_ptr<UI> UIelement1 = std::make_shared<UI>();
	std::shared_ptr<UI> UIelement2 = std::make_shared<UI>();
	std::shared_ptr<UI> loadingText = std::make_shared<UI>(); 
	void setScreen(std::string);
	sf::RectangleShape blankScreen; 
	int playerLives = 3;
	std::shared_ptr<Shop> shop = nullptr;
};