#include "../Game/Game.h"
#include "Start.h"
#include <iostream>

Start::Start()
{
	window = sf::RenderWindow(sf::VideoMode({ 1333, 1000 }), "Fantasy Zone");
	if (!background1.loadFromFile("../res/Title, Intro and Ending Text.png"))
		std::cerr << "Error loading Title Screen";
	backgroundSprite1 = new sf::Sprite(background1);
	//backgroundSprite1->setScale(sf::Vector2f{3.2f,2.5f});
	viewport.setSize(sf::Vector2f{ 250.f,175.f });
	viewport.setCenter(sf::Vector2f{ 840.f,101.5f });
}

Start::~Start()
{
	delete backgroundSprite1;
}

void Start::displayStartScreen()
{
	window.setView(viewport);
	window.draw(*backgroundSprite1);
	window.display();
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::KeyPressed>())
			{
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
				{
					runGame();
				}
			}
		}
	}
}

void Start::runGame()
{
	Game game;
	game.run();
}