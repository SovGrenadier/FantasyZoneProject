#include<../../src/Game/Game.h>
#include <iostream>

Game::Game()
{
    window = sf::RenderWindow(sf::VideoMode({ 1333, 1000 }), "Fantasy Zone");
    if (!background1.loadFromFile("../res/Levels/Round 1 Wrapped.png"))
        std::cerr << "Error loading Round 1 Wrapped.png";
    backgroundSprite1 = new sf::Sprite(background1);
    //backgroundSprite1->setScale(sf::Vector2f{3.2f,2.5f});
    viewport.setSize(sf::Vector2f{ 250.f,175.f });
    viewport.setCenter(sf::Vector2f{840.f,101.5f});
    initialize(); 
    player->initialize(); 
    player->getView(&viewport);
    tick = 0;
    entities = player->getEntities();
    leafDummy = new Leaf(pos);
}

Game::~Game()
{
    delete backgroundSprite1;
}

void Game::run()
{
    window.setFramerateLimit(60);
    while (window.isOpen())
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
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S)
                {
                    //make sure third bit isn't already set to 1
                    if (((input % 0b00001000) / 0b00000100) == 0)
                        input += 0b00000100;
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D)
                {
                    //ensure that a isn't already pressed
                    if (((input % 0b00000100) / 0b00000010) == 0)
                    {
                        //make sure fourth bit isn't already set to 1
                        if (((input % 0b00010000) / 0b00001000) == 0)
                            input += 0b00001000;
                    }
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
                {
                    //make sure second bit isn't already set to 1
                    if (((input % 0b00000100) / 0b00000010) == 0)
                        input += 0b00000010;
                    //if a is pressed and d is pressed a takes priority
                    if (((input % 0b00010000) / 0b00001000) == 1)
                        input -= 0b00001000;
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00000010) / 0b00000001) == 0)
                        input += 0b00000001;
                    //if w and s are pressed w takes priority
                    if (((input % 0b00001000) / 0b00000100) == 1)
                        input -= 0b00000100;
                }
                if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
                    window.close();
				
            }
            if (event->is<sf::Event::KeyReleased>())
            {
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::W)
                {
                    //make sure first bit isn't already set to 0
                    if (((input % 0b00000010) / 0b00000001) == 1)
                        input -= 0b00000001;
                }
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::A)
                {
                    //make sure first bit isn't already set to 0
                    if (((input % 0b00000100) / 0b00000010) == 1)
                        input -= 0b00000010;
                }
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::S)
                {
                    //make sure first bit isn't already set to 0
                    if (((input % 0b00001000) / 0b00000100) == 1)
                        input -= 0b00000100;
                }
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)
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
        window.clear();
        checkCollision();
        window.setView(viewport);
        window.draw(*backgroundSprite1);
        //sf::Vertex test{ player.getSprite()->getPosition(), sf::Color::Red };
        //window.draw(&(test), 1, sf::PrimitiveType::Points);
        updateEntities();
        drawEntities();
        window.display();
        tick += 1;
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

        for(int x=i+1; x<entities->size(); x++)
        {
			if (i != x && entities->at(x)->alive && entities->at(i)->alive)   
            {
                //Check for collisions between player and enemies
                if (!entities->at(x)->ownWeapon &&
                    std::dynamic_pointer_cast<Player>(entities->at(i)) != nullptr)
                {
                    entity1 = entities->at(i)->getSprite()->getGlobalBounds();
                    entity2 = entities->at(x)->getSprite()->getGlobalBounds();
                }
                else if (entities->at(i)->ownWeapon &&
                    std::dynamic_pointer_cast<Enemy>(entities->at(x)) != nullptr)
                {
                    entity1 = entities->at(i)->getSprite()->getGlobalBounds();
                    entity2 = entities->at(x)->getSprite()->getGlobalBounds();
                }


                if (entity1.findIntersection(entity2).has_value())
                {
                    entities->at(x)->takeDamage(entities->at(i)->getDamage());
                    entities->at(i)->takeDamage(entities->at(x)->getDamage());
			
                }
            }
		}

        //Remove any enemies that are dead 
        if (!(entities->at(i)->getActive()))
        {
            entities->erase(entities->begin() + i);
            i--;
        }
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
    //bottaco, snake, scissors, moocolon
    int randEnemy = getRandomInt(1, 4);

    switch (randEnemy)
    {
    case 1:
        //bottaco wave spawn logic
        break;
    case 2:
        //snake wave spawn logic
        break;
    case 3:
        //scissors wave spawn logic
        break;
    case 4:
        //moocolon wave spawn logic
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
}

void Game::initialize()
{
    snakeDummy->initialize(); 
    snakeDummy2->initialize(); 
    scissorsDummy->initialize();
    moocolonDummy->initialize(); 
    kiriDummy->initialize(); 
    bottacoDummy->initialize();
    
    spawnerDummy->initialize();
    spawnerDummy2->initialize();
    spawnerDummy3->initialize();
    spawnerDummy4->initialize();
    spawnerDummy5->initialize();

    stumpalon->initialize(); 
}