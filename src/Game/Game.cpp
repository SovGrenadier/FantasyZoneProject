#include<../../src/Game/Game.h>


Game::Game()
{
    window = sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "SFML works!");
    background1.loadFromFile("../res/Levels/Round 1 - Plaleaf.png");
    backgroundSprite1 = new sf::Sprite(background1);
    //backgroundSprite1->setScale(sf::Vector2f{3.2f,2.5f});
    viewport.setSize(sf::Vector2f{ 250.f,175.f });
    viewport.setCenter(sf::Vector2f{330.f,290.f});
}

Game::~Game()
{

}

void Game::run()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        viewport.move({ 2.0f,0.0f });
        window.clear();
        window.setView(viewport);
        window.draw(*backgroundSprite1);
        //window.draw(*player.getSprite());
        window.display();
    }
}