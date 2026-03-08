#include "../Shop/Shop.h"
#include <iostream>

Shop::Shop()
{
	curState = NOT_ACTIVE;
	
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
	sf::FloatRect bounds = exitSprite->getLocalBounds();
	exitSprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y });

	sprite->setPosition({ 790.f, 25.f });
	exitSprite->setPosition({ 790.f, 180.f });

	usedThisLevel = false;
	set_visible = false;
}


Shop::~Shop()
{
	delete sprite;
	delete cursorSprite;
	delete exitSprite;
	delete texture;
}


void Shop::update(int input)
{  
	switch (curState)
	{
	case NOT_ACTIVE:
		if(/*player has enough money &&*/ !usedThisLevel)
			curState = FLYING;
		break;
	case FLYING:
		set_visible = true;
		//if collision with player
		//curState = BUY_PHASE;
		//else player never collides and shop despawns
		//curState = NOT_ACTIVE;
		//usedThisLevel = true;
		break;
	case BUY_PHASE:
		
		switch(input)
		{

		}


		//when exit button is pressed
		//go to parts select
		curState = PARTS_SELECT;
		break;
	case PARTS_SELECT:
		
		//after selecting parts and exit
		curState = NOT_ACTIVE;
		break;
	}
}


void Shop::death()
{

}