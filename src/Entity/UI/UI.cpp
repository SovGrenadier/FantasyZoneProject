#include "UI.h"
#include <string.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

UI::UI()
{
    font = new sf::Font();
    if (!font->openFromFile("../res/Fonts/determination.ttf"))
		std::cerr << "Failed to load font in UI\n";
    text = new sf::Text(*font, "BING BONG", 25);
	text->setCharacterSize(25);
	text->setPosition({ 800.f, 32.f });//temp value
}

UI::~UI()
{
    delete font;
    delete text;
}

void UI::setText(string newText)
{
	text->setString(newText);
}

void UI::setPosition(sf::Vector2f x)
{
    text->setPosition(x);
}

sf::Text* UI::getText()
{
    return text;
}
