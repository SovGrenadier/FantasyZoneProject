#include"Player.h"

Player::Player()
{
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);

}

Player::~Player()
{
	delete texture;
	delete sprite;
}