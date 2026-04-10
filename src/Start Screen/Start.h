#pragma once
#include "../Game/Game.h"
#include <iostream>

class Start
{
public:
	Start();
	~Start();
	void displayStartScreen();

private:
	sf::RenderWindow window;
	sf::Texture background1;
	sf::Sprite* backgroundSprite1;
	sf::View viewport;
};