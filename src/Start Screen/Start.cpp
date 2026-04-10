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

void Start::displayStartScreen()
{
	window.setView(viewport);
	window.draw(*backgroundSprite1);
	window.display();
}