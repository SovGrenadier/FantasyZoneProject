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
	font->setSmooth(false);
    text = new sf::Text(*font, "BING BONG", 25);
	text->setFillColor(sf::Color::Black);
	text->setCharacterSize(12);
	text->setScale(sf::Vector2f(.75f, .5f));
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
