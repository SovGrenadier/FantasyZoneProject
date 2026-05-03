#define W_PRESSED 0b00000001
#define A_PRESSED 0b00000010
#define S_PRESSED 0b00000100
#define D_PRESSED 0b00001000
#define W_D_PRESSED 0b00001001
#define S_D_PRESSED 0b00001100
#define W_A_PRESSED 0b00000011
#define S_A_PRESSED 0b00000110
#define X_PRESSED 0b00010000
#define Z_PRESSED 0b00100000

#include "../Shop/Shop.h"


Shop::Shop()
{
	curState = FLYING;
	pos = { viewport->getCenter().x, -10.f };

	//appears on screen after two destroyed spawners
	texture = new sf::Texture();
	if (!texture->loadFromFile("../res/Shop Transparent.png"))
		std::cout << "Fail loading Shop.png\n";
	
	ballonSprite = new sf::Sprite(*texture);
	ballonSprite->setTextureRect({ {387, 170},{16,16} });
	sprite = new sf::Sprite(*texture);
	sprite = ballonSprite;
	
	//sprite with parts to buy
	shopSprite = new sf::Sprite(*texture);
	shopSprite->setTextureRect({ {19,22},{470,147} });
	shopSprite->setScale({ 1.f, 0.90f });
	sf::FloatRect bounds = shopSprite->getLocalBounds();
	shopSprite->setOrigin({ shopSprite->getOrigin().x, bounds.size.y / 2.f });
	//the cursor
	cursorSprite = new sf::Sprite(*texture);
	cursorSprite->setTextureRect({ {5,170},{21,13} });
	//the exit button
	exitSprite = new sf::Sprite(*texture);
	exitSprite->setTextureRect({ {30,169},{40,16} });
	bounds = exitSprite->getLocalBounds();
	exitSprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	

	exitUI = new UI;
	exitUI->setText("EXIT");
	
	

	
	topRect.setSize({200.f, 25.f});
	topRect.setPosition({ viewport->getCenter().x, viewport->getCenter().y - 100.f });
	topRect.setFillColor(sf::Color(170, 170, 255, 255));
	usedThisLevel = false;
	boughtItem = true;
	scorePtr = nullptr;
	playerPtr = nullptr;

	time = 0.f;
	yTraveled = 0.f;
	xTraveled = 0.f;
	speed = .8f;
	baseY = 55.f;
	frequency = 0.5f;
	
	ballonSprite->setPosition(pos);
}


Shop::~Shop()
{
	delete cursorSprite;
	delete exitSprite;
	delete ballonSprite;
	delete shopSprite;
	delete exitUI;
	playerPtr = nullptr;
	scorePtr = nullptr;
}


void Shop::update(int input)
{
	auto hitRoof = roof.findIntersection(cursorSprite->getGlobalBounds()).has_value();
	auto hitFloor = floor.findIntersection(cursorSprite->getGlobalBounds()).has_value();
	auto hitRightBarrier = rightBarrier.findIntersection(cursorSprite->getGlobalBounds()).has_value();
	auto hitLeftBarrier = leftBarrier.findIntersection(cursorSprite->getGlobalBounds()).has_value();

	switch (curState)
	{
	case NOT_ACTIVE:
		set_visible = false;
		break;
	case FLYING:
		set_visible = true;
		move();
		//curState = BUY_PHASE;
		//else player never collides and shop despawns
		//curState = NOT_ACTIVE;
		//usedThisLevel = true;
		break;
	case BUY_PHASE:
		usedThisLevel = true;
		switch (input)
		{
		case W_PRESSED:
			if (!hitRoof)
				cursorSprite->move({ 0.f, -2.f });
			break;
		case A_PRESSED:
			if (hitLeftBarrier)
				moveShopItems({ 2.2f, 0.f });
				else
				cursorSprite->move({ -2.2f, 0.f });
			checkShopPosition();
			break;
		case S_PRESSED:
			if (!hitFloor)
				cursorSprite->move({ 0.f, 2.f });
			break;
		case D_PRESSED:
			if (hitRightBarrier)
				moveShopItems({ -2.2f, 0.f });
			else
				cursorSprite->move({ 2.2f, 0.f });
			checkShopPosition();
			break;
		case W_D_PRESSED: 
			if (hitRoof && !hitRightBarrier)
				cursorSprite->move({ 2.2f, 0.f });
			else if (!hitRoof && hitRightBarrier)
			{
				cursorSprite->move({ 0.f, -2.f });
				moveShopItems({ -2.2f, 0.f });
			}
			else if (hitRoof && hitRightBarrier)
				moveShopItems({ -2.2f,0.f });
			else
				cursorSprite->move({ 2.2f,-2.f });

			checkShopPosition();
			break;
		case S_D_PRESSED:
			if (hitFloor && !hitRightBarrier)
				cursorSprite->move({ 2.2, 0.f });
			else if (!hitFloor && hitRightBarrier)
			{
				cursorSprite->move({ 0.f,2.f });
				moveShopItems({ -2.2f,0.f });
			}
			else if (hitFloor && hitRightBarrier)
				moveShopItems({ -2.2f,0.f });
			else
				cursorSprite->move({ 2.2f, 2.f });

			checkShopPosition();
			break;
		case W_A_PRESSED:
			if (hitRoof && !hitLeftBarrier)
				cursorSprite->move({ -2.2f,0.f });
			else if (!hitRoof && hitLeftBarrier)
			{
				cursorSprite->move({ 0.f, -2.f });
				moveShopItems({ 2.2f, 0.f });
			}
			else if (hitRoof && hitLeftBarrier)
				moveShopItems({ 2.2f,0.f });
			else
				cursorSprite->move({ -2.2,-2.f });
			checkShopPosition();
			break;
		case S_A_PRESSED:
			if (hitFloor && !hitLeftBarrier)
				cursorSprite->move({ -2.2, 0.f });
			else if (!hitFloor && hitLeftBarrier)
			{
				cursorSprite->move({ 0.f,2.f });
				moveShopItems({ 2.2f,0.f });
			}
			else if (hitFloor && hitLeftBarrier)
				moveShopItems({ 2.2f,0.f });
			else
				cursorSprite->move({ -2.2f, 2.f });

			checkShopPosition();
			break;
		case X_PRESSED:
			checkCollison();
			break;
		case Z_PRESSED:
			checkCollison();
			break;
		default:

			break;
		}
		
		//when exit button is pressed
		//go to parts select
		//curState = PARTS_SELECT;
		break;
	case PARTS_SELECT:
		switch (input)
		{
		case W_PRESSED:
			//move up one
			break;
		case S_PRESSED:
			//move down one
			break;
		case X_PRESSED:
		case Z_PRESSED:

			break;


		}


		for (int i = 0; i < 40; i++)
		{
			std::cout << i << std::endl;
		}
		applyEffects();
		curState = NOT_ACTIVE;
		break;
	}
}


sf::Sprite* Shop::getSprite()
{
	if (curState == FLYING)
		return ballonSprite;
	else 
		return shopSprite;
}


void Shop::move()
{
	if(yTraveled < 65.f)
	{
		pos.y += 1.f;
		pos.x += 0.25f;
		yTraveled += 1.f;
		ballonSprite->setPosition(pos);
	}
	else if (xTraveled > 205.f)
	{
		pos.y -= 2.f;
		ballonSprite->setPosition(pos);
		sprite->setPosition(pos);
		if (!isOnScreen(*viewport))
			curState = NOT_ACTIVE;
	}
	else
	{
		float wave = static_cast<float>(sin(time * frequency));	
		pos.x += speed;
		xTraveled += speed;
		pos.y = baseY + (time * wave);
		ballonSprite->setPosition(pos);
		time += 0.2;
	}
}


std::vector <sf::Drawable*> Shop::getSprites()
{
	if (curState == BUY_PHASE)
	{
		std::vector <sf::Drawable*> drawables;
	
		drawables.push_back(shopSprite);
		drawables.push_back(exitSprite);
		for (int i = 0; i < shopItems.size(); i++)
			if(shopItems[i]->getBoughtStatus())
				drawables.push_back(shopItems[i]->getSoldSprite());
		drawables.push_back(cursorSprite);
		return drawables;
	}
	else if (curState == PARTS_SELECT)
	{
		std::vector <sf::Drawable*> drawables;
		drawables.push_back(exitUI->getText());
		return drawables;
	}
}


void Shop::setSpritePositions(int* score, Player* player)
{
	scorePtr = score;
	playerPtr = player;
	sf::Vector2f center = viewport->getCenter();
	sf::Vector2f size = viewport->getSize();
	size /= 2.f;

	roof.position = { center.x - size.x, center.y - size.y + 10.f };
	roof.size = { size.x * 2, 15.f };
	
	floor.position = { center.x - size.x, center.y + size.y - 5.f };
	floor.size = roof.size;


	leftBarrier.position = {center.x - size.x, 0 };
	leftBarrier.size = {15.f, size.y * 2 + 20.f};
	
	rightBarrier.position = { center.x + size.x - 10.f , 0 };
	rightBarrier.size = leftBarrier.size;

	sf::Vector2f position = viewport->getCenter();
	position.x = viewport->getCenter().x;
	position.x -= 115;
	position.x += 20;
	position.y -= 43;
	
	/*temporary.setSize({1.f,1.f});
	temporary.setPosition(position);
	temporary.setFillColor(sf::Color::Black);
	temporary2.setSize(leftBarrier.size);
	temporary2.setPosition(leftBarrier.position);
	temporary2.setFillColor(sf::Color::Black);*/

	viewCenterOld = viewport->getCenter();
	exitUI->setPosition({ viewCenterOld.x - 20, viewCenterOld.y - 50.f });


	pos = { center.x, -10.f };
	ballonSprite->setPosition(pos);
	cursorSprite->setPosition({center.x, center.y + 60.f});
	exitSprite->setPosition({ viewport->getCenter().x, viewport->getSize().y });
	shopSprite->setPosition({ center.x - size.x + 10.f, center.y });
	usedThisLevel = true;

	createShopItems();
}


void Shop::checkCollison()
{
	if(curState == BUY_PHASE)
	{
		sf::Vector2f cursor(cursorSprite->getPosition());
		sf::FloatRect exitButton(exitSprite->getGlobalBounds());
		cursor.y += 10.f;
		if (exitButton.contains(cursor))
		{
			if (!boughtItem)
				curState = NOT_ACTIVE;
			else
				curState = PARTS_SELECT;
			viewport->setCenter(viewCenterOld);
		}
		for (int i = 0; i < shopItems.size(); i++)
		{
			if (shopItems[i]->getBox().contains(cursor))
			{
				int value = shopItems[i]->getValue();
				if (*scorePtr > value && scorePtr != nullptr && !shopItems[i]->getBoughtStatus())
				{
					*scorePtr -= value;
					shopItems[i]->setBought(true);
					if (*scorePtr == 0)
						curState == PARTS_SELECT;
				}
				
				return;
			}
		}
	}
}


void Shop::checkShopPosition()
{
	sf::Vector2f center = viewport->getCenter();
	sf::Vector2f size = viewport->getSize();
	size /= 2.f;

	sf::Vector2f pos = shopSprite->getPosition();
	sf::FloatRect bounds = shopSprite->getGlobalBounds();

	float leftLimit = center.x - size.x + 10.f;
	float rightLimit = center.x + size.x - 10.f;

	if (bounds.position.x > leftLimit)
		pos.x = leftLimit;
	if (bounds.position.x + bounds.size.x < rightLimit)
		pos.x += rightLimit - (bounds.position.x + bounds.size.x);

	shopSprite->setPosition(pos);
}


void Shop::createShopItems()
{
	sf::Vector2f size = { 73,61 };
	sf::Vector2f position = viewport->getCenter();
	sf::Vector2f padding = { 79.f,61.f };
	std::cout << "X: " << position.x << " Y: " << position.y << "\n";
	position.x = viewport->getCenter().x;
	position.x -= 100;
	position.y -= 50;

	shopItems.push_back(new ShopItem(position, size ,100, ShopItem::BigWings));
	shopItems.push_back(new ShopItem({position.x + padding.x, position.y}, size, 5000, ShopItem::TurboEngine));
	
	shopItems.push_back(new ShopItem({position.x, position.y + padding.y}, size, 500, ShopItem::JetEngine));
	shopItems.push_back(new ShopItem({position + padding }, size, 30000, ShopItem::RocketEngine)); 
	
	shopItems.push_back(new ShopItem({position.x + (padding.x * 2.f), position.y }, size, 500, ShopItem::LaserBeam));
	shopItems.push_back(new ShopItem({position.x + (padding.x * 2.f), position.y + padding.y}, size, 1000, ShopItem::WideBeam));
	
	shopItems.push_back(new ShopItem({position.x + (padding.x * 3.f), position.y }, size, 2500, ShopItem::SevenWayShot));
	shopItems.push_back(new ShopItem({position.x + (padding.x * 3.f), position.y + padding.y}, size, 100, ShopItem::TwinBombs));
	
	shopItems.push_back(new ShopItem({position.x + (padding.x * 4.f), position.y }, size, 1000,ShopItem::FireBomb));
	shopItems.push_back(new ShopItem({position.x + (padding.x * 4.f), position.y + padding.y}, size, 1000, ShopItem::SmartBomb));
	
	shopItems.push_back(new ShopItem({position.x + (padding.x * 5.f), position.y }, size, 1000, ShopItem::HeavyBomb));
	shopItems.push_back(new ShopItem({position.x + (padding.x * 5.f), position.y + padding.y}, size, 2500, ShopItem::ExtraShip));
}


void Shop::moveShopItems(sf::Vector2f pos)
{
	if (!canMoveShopItems(pos))
		return;
	shopSprite->move(pos);
	for (int i = 0; i < shopItems.size(); i++)
		shopItems[i]->moveSprite(pos);
}


bool Shop::canMoveShopItems(sf::Vector2f movement)
{
	sf::FloatRect bounds = shopSprite->getGlobalBounds();

	float screenLeft = viewport->getCenter().x - viewport->getSize().x / 2.f + 10.f;
	float screenRight = viewport->getCenter().x + viewport->getSize().x / 2.f - 10.f;

	float nextLeft = bounds.position.x + movement.x;
	float nextRight = bounds.position.x + bounds.size.x + movement.x;

	if (movement.x > 0 && nextLeft > screenLeft)
		return false;

	if (movement.x < 0 && nextRight < screenRight)
		return false;

	return true;
}


void Shop::applyEffects()
{
	std::vector <ShopItem*> boughtItems;
	for (int i = 0; i < shopItems.size(); i++)
		if (shopItems[i]->getBoughtStatus())
			boughtItems.push_back(shopItems[i]);

	for (int i = 0; i < boughtItems.size(); i++)
	{
		if (boughtItems[i]->getType() == ShopItem::ExtraShip)
			playerPtr->setLives(playerPtr->getLives() + 1);
	}


}