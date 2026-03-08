#include "../Shop/Shop.h"
#include <iostream>

Shop::Shop()
{
	//appears on screen after two destroyed spawners
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Shop.png"))
		std::cout << "Fail loading Shop.png\n";
	//sprite with parts to buy
	sprite = new sf::Sprite(*texture);
	sprite->setTextureRect({ {19,27},{470,137} });
	//the cursor
	cursorSprite = new sf::Sprite(*texture);
	cursorSprite->setTextureRect({ {5,170},{13,21} });
	//the exit button
	exitSprite = new sf::Sprite(*texture);
	exitSprite->setTextureRect({ {30,169},{40,16} });
	sprite->setPosition({ 790.f, 25.f });
}


Shop::~Shop()
{




	delete shopSprite;
	delete cursorSprite;
	delete exitSprite;
}


void Shop::update(int input)
{  
	switch (curState)
	{
	case NOT_ACTIVE:

		break;
	case FLYING:

		break;
	case BUY_PHASE:
		cursorPos = {};
		switch(input)
		{

		}



		break;
	case PARTS_SELECT:

		break;
	}
}


void Shop::death()
{

}