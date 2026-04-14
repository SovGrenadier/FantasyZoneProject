#pragma once
//#include "../Entity.h"
#include <string.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace std;

class UI
{
public:
	UI();
	~UI();
	void setText(string);
	void setPosition(sf::Vector2f);
	void update();
	sf::Text* getText();

private:
	sf::Font* font;
	sf::Text* text;

};

