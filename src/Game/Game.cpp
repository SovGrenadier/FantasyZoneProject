#include<../../src/Game/Game.h>

Game::Game()
{
    window = sf::RenderWindow(sf::VideoMode({ 1333, 1000 }), "Fantasy Zone");
    background1.loadFromFile("../res/Levels/Round 1.png");
    backgroundSprite1 = new sf::Sprite(background1);
    //backgroundSprite1->setScale(sf::Vector2f{3.2f,2.5f});
    viewport.setSize(sf::Vector2f{ 250.f,175.f });
    viewport.setCenter(sf::Vector2f{330.f,285.f});
    player.getView(&viewport);
    tick = 0;
    entities = player.getEntities();
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
            if (event->is<sf::Event::KeyPressed>())
            {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::X)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00010000) / 0b00001000) == 0)
                        input += 0b00010000;
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00001000) / 0b00000100) == 0)
                        input += 0b00000100;
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00010000) / 0b00001000) == 0)
                        input += 0b00001000;
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00000100) / 0b00000010) == 0)
                        input += 0b00000010;
                    //if a is pressed and d is pressed a takes priority
                    if (((input % 0b00010000) / 0b00001000) == 0)
                        input -= 0b00001000;
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00000010) / 0b00000001) == 0)
                        input += 0b00000001;
                    //if w and s are pressed w takes priority
                    if (((input % 0b00010000) / 0b00001000) == 0)
                        input += 0b00001000;
                }
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
                        input += 0b00000010;
                }
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::S)
                {
                    //make sure first bit isn't already set to 0
                    if (((input % 0b00001000) / 0b00000100) == 1)
                        input += 0b00000100;
                }
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D)
                {
                    //make sure first bit isn't already set to 0
                    if (((input % 0b00010000) / 0b00001000) == 1)
                        input += 0b00001000;
                }
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::X)
                {
                    //make sure first bit isn't already set to 1
                    if (((input % 0b00010000) / 0b00001000) == 1)
                        input -= 0b00010000;
                }
            }
        }

        //viewport.move({ 2.0f,0.0f });
        window.clear();
        window.setView(viewport);
        window.draw(*backgroundSprite1);
        
        updateEntities();
        drawEntities();
        window.display();
        tick += 1;
    }
}


void Game::updateEntities()
{
    for (int i{}; i < entities->size(); i++)
    {
        (entities->at(i))->update(input);
    }
}

void Game::drawEntities()
{
    for (int i{}; i < entities->size(); i++)
    {
        window.draw(*((entities->at(i))->getSprite()));
    }
}