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

	topRect.setSize({200.f, 25.f});
	topRect.setPosition({ viewport->getCenter().x, viewport->getCenter().y - 100.f });
	topRect.setFillColor(sf::Color(170, 170, 255, 255));
	usedThisLevel = false;
	set_visible = false;
	
	time = 0.f;
	yTraveled = 0.f;
	xTraveled = 0.f;
	speed = .8f;
	baseY = 55.f;
	frequency = 0.5f;

	ballonSprite->setPosition(pos);
	spriteMov = { 0.f,0.f };
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
			spriteMov = { 0.f, -2.f };
			break;
		case A_PRESSED:
			spriteMov = { -2.2f, 0.f };
			break;
		case S_PRESSED:
			spriteMov = { 0.f, 2.f };
			break;
		case D_PRESSED:
			spriteMov = { 2.2f,0.f };
			break;
		case W_D_PRESSED:
			spriteMov = { 2.2f, -2.f };
			break;
		case S_D_PRESSED:
			spriteMov = { 2.2f, 2.f };
			break;
		case W_A_PRESSED:
			spriteMov = { -2.2f, -2.f };
			break;
		case S_A_PRESSED:
			spriteMov = { -2.2f, 2.f };
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

		cursorSprite->move(spriteMov);
		spriteMov = { 0.f, 0.f };
		//when exit button is pressed
		//go to parts select
		//curState = PARTS_SELECT;
		break;
	case PARTS_SELECT:

		//after selecting parts and exit
		curState = NOT_ACTIVE;
		break;
	}
}


sf::Sprite* Shop::getSprite()
{
	if (curState == FLYING)
		return ballonSprite;
	else 
		return cursorSprite;
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


std::vector <sf::Sprite*> Shop::getSprites()
{
	if (curState == BUY_PHASE)
	{
		std::vector <sf::Sprite*> temp;
		temp.push_back(shopSprite);
		temp.push_back(exitSprite);
		temp.push_back(cursorSprite);
		return temp;
	}
	else
	{
		std::vector <sf::Sprite*> temp;
		temp.push_back(shopSprite);
		temp.push_back(exitSprite);
		return temp;
	}
}


void Shop::setSpritePositions()
{
	sf::Vector2f center = viewport->getCenter();
	sf::Vector2f size = viewport->getSize();
	size /= 2.f;

	pos = { center.x, -10.f };
	ballonSprite->setPosition(pos);
	cursorSprite->setPosition({center.x, center.y + 60.f});
	exitSprite->setPosition({ viewport->getCenter().x, viewport->getSize().y });
	shopSprite->setPosition({ center.x - size.x + 15.f, center.y });
	usedThisLevel = true;
}


void Shop::checkCollison()
{
	sf::FloatRect cursor(cursorSprite->getLocalBounds());
	sf::FloatRect exitButton(exitSprite->getLocalBounds());
	if (cursor.findIntersection(exitButton).has_value())
	{
		curState = NOT_ACTIVE;
	}
}