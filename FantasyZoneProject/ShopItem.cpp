#include "../src/Entity/Shop/ShopItem/ShopItem.h"

ShopItem::ShopItem(sf::Vector2f soldOutPosition, sf::Vector2f size, int value, ItemType type)
{
	itemTexture = new sf::Texture();
	if (!itemTexture->loadFromFile("../res/Shop Transparent.png"))
		std::cerr << "item texture failed to load shop.png\n";

	soldOutSprite = new sf::Sprite(*itemTexture);
	soldOutSprite->setTextureRect({ {76,169},{40,16} });
	soldOutSprite->setPosition(soldOutPosition);

	this->soldOutPosition = soldOutPosition;
	this->value = value;
	this->type = type;

	boundary.size = size;
	boundary.position = soldOutPosition;
	boundary.position.x -= 15.f;
	boundary.position.y -= 12.f;
	bought = false;
}


ShopItem::~ShopItem()
{
	delete soldOutSprite;
	delete itemTexture;
	itemTexture = nullptr;
	soldOutSprite = nullptr;
}


sf::Sprite* ShopItem::getSoldSprite()
{
	if (bought)
		return soldOutSprite;
	else
		return soldOutSprite;
}


void ShopItem::moveSprite(sf::Vector2f pos)
{
	soldOutSprite->move(pos);
	boundary.position.x += pos.x;
	boundary.position.y += pos.y;
}


std::string ShopItem::getItemTitle()
{
	if (type == BigWings)
		return "BIG WINGS";
	else if (type == TurboEngine)
		return "TURBO ENGINE";
	else if (type == LaserBeam)
		return "LASER BEAM";
	else if (type == SevenWayShot)
		return "7 WAY SHOT";
	else if (type == FireBomb)
		return "FIRE BOMB";
	else if (type == HeavyBomb)
		return "HEAVY BOMB";
	else if (type == JetEngine)
		return "JET ENGINE";
	else if (type == RocketEngine)
		return "ROCKET ENGINE";
	else if (type == WideBeam)
		return "WIDE BEAM";
	else if (type == TwinBombs)
		return "TWIN BOMBS";
	else if (type == SmartBomb)
		return "SMART BOMB";
}