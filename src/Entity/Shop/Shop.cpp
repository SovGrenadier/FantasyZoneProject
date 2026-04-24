#include "../Shop/Shop.h"
#include <iostream>

Shop::Shop()
{
	curState = FLYING;
	
	//appears on screen after two destroyed spawners
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Shop.png"))
		std::cout << "Fail loading Shop.png\n";
	ballonSprite = new sf::Sprite(*texture);
	ballonSprite->setTextureRect({ {387, 170},{16,16} });
	//sprite with parts to buy
	shopSprite = new sf::Sprite(*texture);
	shopSprite->setTextureRect({ {19,27},{470,137} });
	//the cursor
	cursorSprite = new sf::Sprite(*texture);
	cursorSprite->setTextureRect({ {5,170},{13,21} });
	//the exit button
	exitSprite = new sf::Sprite(*texture);
	exitSprite->setTextureRect({ {30,169},{40,16} });
	sf::FloatRect bounds = exitSprite->getLocalBounds();
	exitSprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y });

	/*sf::Vector2f center = viewport->getCenter();
	
	ballonSprite->setPosition({center.x, 0.f});

	shopSprite->setPosition(center);
	cursorSprite->setPosition(center);*/
	usedThisLevel = false;
	set_visible = false;
}


Shop::~Shop()
{
	delete cursorSprite;
	delete exitSprite;
	delete ballonSprite;
	delete shopSprite;
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