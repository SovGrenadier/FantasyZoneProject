#include<../../src/Game/Game.h>
#include <iostream>
#include<algorithm>

Game::Game()
{
	window = sf::RenderWindow(sf::VideoMode({ 1333, 1000 }), "Fantasy Zone");
	if (!background1.loadFromFile("../res/Title, Intro and Ending Text.png"))
		std::cerr << "Error loading Title Screen";
	backgroundSprite1 = new sf::Sprite(background1);
	//backgroundSprite1->setScale(sf::Vector2f{3.2f,2.5f});
	viewport.setSize(sf::Vector2f{ 250.f,175.f });
	viewport.setCenter(sf::Vector2f{ 840.f,101.5f });
	viewportStart.setSize(sf::Vector2f{ 253.f,197.f });
	viewportStart.setCenter(sf::Vector2f{ 140.5f,108.5f });
	player->initialize();
	initialize();
	player->getView(&viewport);
	tick = 0;
	offset = { -120.f,-88.f };
	score = 0;
	entities = player->getEntities();

	spawnerDummy->getPlayer(player);
	spawnerDummy2->getPlayer(player);
	spawnerDummy3->getPlayer(player);
	spawnerDummy4->getPlayer(player);
	spawnerDummy5->getPlayer(player);
	spawnerDummy6->getPlayer(player);
	spawnerDummy7->getPlayer(player);
	spawnerDummy8->getPlayer(player);
	//std::make_shared<Boss>()->initialize();
}

Game::~Game()
{
	delete backgroundSprite1;
}

void Game::run()
{
	window.setFramerateLimit(60);

	while (window.isOpen() && !start)
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::KeyPressed>())
			{
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
					window.close();
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::X)
					start = true;
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Z)
					start = true;
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::I)
					invincible = true;
			}
		}
		window.setView(viewportStart);
		if (tick > 120 && tick < 480 * 4)
			viewportStart.move({ 0.f,0.25f });
		window.clear();
		window.draw(*backgroundSprite1);
		window.display();
		tick++;
	}
	if (invincible)
		player->setHealth();
	background1.~Texture();
	if (!background1.loadFromFile("../res/Levels/Round 1 Wrapped.png"))
		std::cerr << "Error loading Level Background";
	backgroundSprite1 = new sf::Sprite(background1);

	while (window.isOpen() && start)
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			//check header file to see more info on input
			if (event->is<sf::Event::KeyPressed>())
			{
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::X)
				{
					//make sure fifth bit isn't already set to 1
					if (((input % 0b00100000) / 0b00010000) == 0)
						input += 0b00010000;
				}
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Z)
				{
					//make sure fifth bit isn't already set to 1
					if (((input % 0b01000000) / 0b00100000) == 0)
						input += 0b00100000;
				}
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down)
				{
					//make sure third bit isn't already set to 1
					if (((input % 0b00001000) / 0b00000100) == 0)
						input += 0b00000100;
				}
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right)
				{
					//ensure that a isn't already pressed
					if (((input % 0b00000100) / 0b00000010) == 0)
					{
						//make sure fourth bit isn't already set to 1
						if (((input % 0b00010000) / 0b00001000) == 0)
							input += 0b00001000;
					}
				}
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left)
				{
					//make sure second bit isn't already set to 1
					if (((input % 0b00000100) / 0b00000010) == 0)
						input += 0b00000010;
					//if a is pressed and d is pressed a takes priority
					if (((input % 0b00010000) / 0b00001000) == 1)
						input -= 0b00001000;
				}
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up)
				{
					//make sure first bit isn't already set to 1
					if (((input % 0b00000010) / 0b00000001) == 0)
						input += 0b00000001;
					//if w and s are pressed w takes priority
					if (((input % 0b00001000) / 0b00000100) == 1)
						input -= 0b00000100;
				}
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
					window.close();

			}
			if (event->is<sf::Event::KeyReleased>())
			{
				if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Up)
				{
					//make sure first bit isn't already set to 0
					if (((input % 0b00000010) / 0b00000001) == 1)
						input -= 0b00000001;
				}
				if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Left)
				{
					//make sure first bit isn't already set to 0
					if (((input % 0b00000100) / 0b00000010) == 1)
						input -= 0b00000010;
				}
				if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Down)
				{
					//make sure first bit isn't already set to 0
					if (((input % 0b00001000) / 0b00000100) == 1)
						input -= 0b00000100;
				}
				if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Right)
				{
					//make sure first bit isn't already set to 0
					if (((input % 0b00010000) / 0b00001000) == 1)
						input -= 0b00001000;
				}
				if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::X)
				{
					//make sure first bit isn't already set to 0
					if (((input % 0b00100000) / 0b00010000) == 1)
						input -= 0b00010000;
				}
				if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Z)
				{
					//make sure first bit isn't already set to 0
					if (((input % 0b01000000) / 0b00100000) == 1)
						input -= 0b00100000;
				}
			}
		}

		const sf::Vector2i mousePosition(sf::Mouse::getPosition(window));
		const sf::Vector2f mouseCoord(window.mapPixelToCoords(mousePosition));
		//std::cout << "X: " << mouseCoord.x << " Y: " << mouseCoord.y << std::endl;
		//bullet->setPosition(mouseCoord); 

		//viewport.move({ 2.0f,0.0f });
		UIelements->setText("Score: " + std::to_string(score));
		if (invincible)
			UIelements->setText("Score: " + std::to_string(score) + "\nInvincible!");
		UIelements->setPosition(viewport.getCenter() + offset);
		window.clear();
		checkCollision();
		if (!(player->alive))
		{
			window.close();
			std::cout << "Game over" << std::endl;
		}
		window.setView(viewport);
		window.draw(*backgroundSprite1);
		window.draw(*UIelements->getText());
		//sf::Vertex test{ player.getSprite()->getPosition(), sf::Color::Red };
		//window.draw(&(test), 1, sf::PrimitiveType::Points);
		updateEntities();
		drawEntities();
		window.display();
		tick += 1;

		if (tick % 500 == 0)
		{
			enemyWave();
			//std::cout << "Player Y: " << player->getSprite()->getPosition().y << "\n";
			//std::cout << "\nPAUSE\n";
		}

		//std::cout << "Tick: " << tick << std::endl;
	}
}


void Game::updateEntities()
{
	for (int i{}; i < entities->size(); i++)
	{
		if ((entities->at(i))->getActive())
			(entities->at(i))->update(input);
	}
	//due to viewport loop some spawner are drawn twice on the entrie background
	//need to make sure these spawners have the same health since they represent the same spawner just on 
	// different sides of the loop
	spawnerDummy->setHeath(std::min(spawnerDummy->getHeath(), spawnerDummy7->getHeath()));
	spawnerDummy7->setHeath(std::min(spawnerDummy->getHeath(), spawnerDummy7->getHeath()));
	spawnerDummy2->setHeath(std::min(spawnerDummy2->getHeath(), spawnerDummy8->getHeath()));
	spawnerDummy8->setHeath(std::min(spawnerDummy2->getHeath(), spawnerDummy8->getHeath()));
}

void Game::drawEntities()
{
	for (int i{}; i < entities->size(); i++)
	{
		if ((entities->at(i))->getVisible())
			window.draw(*((entities->at(i))->getSprite()));
	}
}

void Game::checkCollision()
{
	sf::FloatRect entity1, entity2;

	//std::cout << entities->size() << std::endl;
	for (int i = 0; i < entities->size(); i++)
	{
		//std::cout << entities->size() << std::endl;
		for (int x = i + 1; x < entities->size(); x++)
		{
			if (entities->at(x)->alive && entities->at(i)->alive)
			{ 
				entity1 = entities->at(i)->getSprite()->getGlobalBounds();
				entity2 = entities->at(x)->getSprite()->getGlobalBounds();
				//check if two entities are colliding
				if (entity1.findIntersection(entity2).has_value())
				{
					//determine which 2 entities are colliding and determine action that should be taken
					
					if (std::dynamic_pointer_cast<StumpalonMouth>(entities->at(i)) != nullptr)
					{
						if (std::dynamic_pointer_cast<Bullet>(entities->at(x)) != nullptr)
						{
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
						}
					}
					if (std::dynamic_pointer_cast<Enemy>(entities->at(x)) != nullptr)
					{
						if (std::dynamic_pointer_cast<Player>(entities->at(i)) != nullptr)
						{
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
						}
						else if (std::dynamic_pointer_cast<Bullet>(entities->at(i)) != nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
							score += 100;
						}
						else if (std::dynamic_pointer_cast<Bomb>(entities->at(i)) != nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
							score += 100;
						}
					}
					else if (std::dynamic_pointer_cast<Spawner>(entities->at(x)) != nullptr)
					{
						if (std::dynamic_pointer_cast<Player>(entities->at(i)) != nullptr)
						{
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
						}
						else if (std::dynamic_pointer_cast<Bullet>(entities->at(i)) != nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
						}
						else if (std::dynamic_pointer_cast<Bomb>(entities->at(i)) != nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
						}
					}
					else if (std::dynamic_pointer_cast<Player>(entities->at(x)) != nullptr)
					{
						if (std::dynamic_pointer_cast<Enemy>(entities->at(i)) != nullptr &&
							std::dynamic_pointer_cast<Boss>(entities->at(i)) == nullptr)
						{
							//entities->at(x)->takeDamage(entities->at(i)->getDamage());
						}
						if (std::dynamic_pointer_cast<Spawner>(entities->at(i)))
						{
							//entities->at(x)->takeDamage(entities->at(i)->getDamage());
						}
					}
					else if (std::dynamic_pointer_cast<Bullet>(entities->at(x)) != nullptr)
					{
						if (std::dynamic_pointer_cast<Enemy>(entities->at(i)) != nullptr &&
							std::dynamic_pointer_cast<Boss>(entities->at(i)) == nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
							score += 100;
						}
						if (std::dynamic_pointer_cast<Spawner>(entities->at(i)) != nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
							if (!(entities->at(i)->alive))
								score += 500;
						}
					}
					else if (std::dynamic_pointer_cast<Bomb>(entities->at(x)))
					{
						if (std::dynamic_pointer_cast<Enemy>(entities->at(i)) != nullptr &&
							std::dynamic_pointer_cast<Boss>(entities->at(i)) == nullptr)
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
							score += 100;
						}
						if (std::dynamic_pointer_cast<Spawner>(entities->at(i)))
						{
							entities->at(x)->takeDamage(entities->at(i)->getDamage());
							entities->at(i)->takeDamage(entities->at(x)->getDamage());
							if (!(entities->at(i)->alive))
								score += 500;
						}
					}
				}
			}
		}

		removeDead();

		//Remove any enemies that are dead 
		
		/* for testing
		if (dynamic_cast<Spawner*>(entities->at(i)) != nullptr)
		{
			std::cout << (entities->at(i)->getSprite())->getPosition().x<< std::endl;
			std::cout << (entities->at(i)->getSprite())->getPosition().y << std::endl;
			std::cout << "break" << std::endl;
		}
		*/
	}

}


void Game::enemyWave()
{
	//moocolon, bottaco, scissors, snake
	//ALL VALUES ARE SUBJECT TO CHANGE
	int randEnemy = getRandomInt(1, 4);
	bool formation = getRandomInt(0, 1); // true or false
	bool rightSide = player->getSprite()->getPosition().x < viewport.getCenter().x;
	sf::Vector2f padding = { 0.f,0.f };
	sf::Vector2f spawnPosition = { 0.f,0.f };

	if (rightSide)
	{
		float sizeX = viewport.getSize().x;
		sizeX /= 2.f;
		spawnPosition.x = viewport.getCenter().x + sizeX + 20.f; // extra 20 so it appears off screen

	}
	else //left side
	{
		float sizeX = viewport.getSize().x;
		sizeX /= 2.f;
		spawnPosition.x = viewport.getCenter().x - sizeX - 20.f; // extra 20 so it appears off screen
	}

	switch (randEnemy)
	{
	case 1://moocolon wave spawn logic
		spawnPosition.y = viewport.getCenter().y - 30.f;
		if (formation)// 2x2 square, right side
		{
			padding = { 16.f, 16.f };
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x			 , spawnPosition.y })->initialize();
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x + padding.x , spawnPosition.y + padding.y })->initialize();
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x			 , spawnPosition.y + padding.y })->initialize();
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x + padding.x , spawnPosition.y })->initialize();
		}
		else // column
		{
			padding.y = 40.f;
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x, spawnPosition.y + padding.y })->initialize();
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x, spawnPosition.y })->initialize();
			std::make_shared<Moocolon>(sf::Vector2f{ spawnPosition.x, spawnPosition.y - padding.y })->initialize();
		}
		break;
	case 2: //bottaco wave spawn logic
		if (formation) // one from each side
		{
			padding.x = 20.f;
			spawnPosition.y = viewport.getCenter().y;
			float halfSize = viewport.getSize().x;
			halfSize /= 2.f;
			std::make_shared<Bottaco>(sf::Vector2f{ spawnPosition.x - halfSize + padding.x, spawnPosition.y })->initialize();
			std::make_shared<Bottaco>(sf::Vector2f{ spawnPosition.x + halfSize + padding.x, spawnPosition.y })->initialize();
		}
		else // four row formation from right side
		{
			spawnPosition.y = viewport.getCenter().y;
			padding.y = 20.f;
			std::make_shared<Bottaco>(sf::Vector2f{ spawnPosition.x, spawnPosition.y })->initialize();
			std::make_shared<Bottaco>(sf::Vector2f{ spawnPosition.x, spawnPosition.y + padding.y })->initialize();
			std::make_shared<Bottaco>(sf::Vector2f{ spawnPosition.x, spawnPosition.y + padding.y * 2 })->initialize();
			std::make_shared<Bottaco>(sf::Vector2f{ spawnPosition.x, spawnPosition.y + padding.y * 3 })->initialize();
		}
		break;
	case 3://scissors wave spawn logic
		spawnPosition.y = 0.f;
		if (formation)
		{
			padding = { 20.f, 12.f };
			spawnPosition.y = viewport.getCenter().y;
			std::make_shared<Scissors>(sf::Vector2f{spawnPosition.x - padding.x, spawnPosition.y})->initialize();
			std::make_shared<Scissors>(sf::Vector2f{spawnPosition.x, spawnPosition.y})->initialize();
			std::make_shared<Scissors>(sf::Vector2f{spawnPosition.x + padding.x, spawnPosition.y})->initialize();
			std::make_shared<Scissors>(sf::Vector2f{spawnPosition.x - padding.x, spawnPosition.y - padding.y})->initialize();
			std::make_shared<Scissors>(sf::Vector2f{spawnPosition.x, spawnPosition.y - padding.y})->initialize();
			std::make_shared<Scissors>(sf::Vector2f{spawnPosition.x + padding.x, spawnPosition.y - padding.y})->initialize();
		}
		else if (!formation)
		{
			padding.x = 20.f;
			float quarter = viewport.getCenter().y / 2;
			spawnPosition.y = quarter;
			std::make_shared<Scissors>(sf::Vector2f{ spawnPosition.x - padding.x, spawnPosition.y })->initialize();
			std::make_shared<Scissors>(sf::Vector2f{ spawnPosition.x, spawnPosition.y })->initialize();
			std::make_shared<Scissors>(sf::Vector2f{ spawnPosition.x + padding.x, spawnPosition.y })->initialize();

			spawnPosition.y = viewport.getCenter().y + quarter;
			std::make_shared<Scissors>(sf::Vector2f{ spawnPosition.x - padding.x, spawnPosition.y })->initialize();
			std::make_shared<Scissors>(sf::Vector2f{ spawnPosition.x, spawnPosition.y })->initialize();
			std::make_shared<Scissors>(sf::Vector2f{ spawnPosition.x + padding.x, spawnPosition.y })->initialize();
		}	
		break;
	case 4://snake wave spawn logic
		spawnPosition.y = viewport.getCenter().y;
		if (rightSide)
		{
			float displacement = 45.f;
			padding = { 30.f, 30.f };
			spawnPosition.x += displacement;
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x + 45.f + padding.x	, spawnPosition.y - padding.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x + 45.f				, spawnPosition.y - padding.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x					, spawnPosition.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x + padding.x		, spawnPosition.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x - 45.f				, spawnPosition.y + padding.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x - 45.f + padding.x	, spawnPosition.y + padding.y })->initialize();
		}
		else // left side
		{
			float displacement = 45.f;
			padding = { 30.f, 30.f };
			spawnPosition.x -= displacement;
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x - 45.f - padding.x, spawnPosition.y - padding.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x - 45.f			, spawnPosition.y - padding.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x					, spawnPosition.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x - padding.x		, spawnPosition.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x + 45.f			, spawnPosition.y + padding.y })->initialize();
			std::make_shared<Snake>(sf::Vector2f{ spawnPosition.x + 45.f - padding.x, spawnPosition.y + padding.y })->initialize();
		}
		break;
	default:
		break;
	}
}


int Game::getRandomInt(int min, int max)
{
	//min and max are included, therefore values for (1,3): 1, 2, 3
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}


void Game::initialize()
{
	spawnerDummy->initialize();
	spawnerDummy2->initialize();
	spawnerDummy3->initialize();
	spawnerDummy4->initialize();
	spawnerDummy5->initialize();
	spawnerDummy6->initialize();
	spawnerDummy7->initialize();
	spawnerDummy8->initialize();
}

void Game::removeDead()
{
	for (int i = 0; i < entities->size(); i++)
	{
		if (!(entities->at(i)->getActive()))
		{
			if (std::dynamic_pointer_cast<Spawner>(entities->at(i)) != nullptr)
				spawnerCount--; 
			entities->erase(entities->begin() + i);
			i--;
		}
	}
}

void Game::removeEnemies()
{
	for (int i = 0; i < entities->size(); i++)
	{
		if (std::dynamic_pointer_cast<Enemy>(entities->at(i)) != nullptr)
		{
			entities->erase(entities->begin() + i);
			i--;
		}
	}
}