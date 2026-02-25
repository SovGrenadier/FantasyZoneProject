#include"Player.h"

Player::Player()
{
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	Animation* rightFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{9,37},sf::Vector2i{36,12} });
	Animation* leftFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{69,150},sf::Vector2i{36,12} });
	animations[GLIDE_RIGHT] = rightFly;
	animations[MOVE_RIGHT] = rightFly;
	animations[MOVE_UP_FACE_RIGHT] = rightFly;
	animations[MOVE_DOWN_FACE_RIGHT] = rightFly;
	animations[GLIDE_LEFT] = leftFly;
	animations[MOVE_LEFT] = leftFly;
	animations[MOVE_UP_FACE_LEFT] = leftFly;
	animations[MOVE_DOWN_FACE_LEFT] = leftFly;
	sprite->setPosition(sf::Vector2f{ 790.f,109.f });
	tickRate = 100000;
}

Player::~Player()
{
	delete texture;
	delete sprite;
}


void Player::update(int input)
{
	ticks++;
	//a is pressed
	if (((input % 0b00000100) / 0b00000010) == 1)
		faceRight = false;
	//w is pressedz
	if (((input % 0b00010000) / 0b00001000) == 1)
		faceRight = true;
	if (input == 0b00010000)
		shoot();
	switch (input)
	{
	case 0b00000000:
		if (faceRight)
		{
			curAction = GLIDE_RIGHT;
			spriteMov = { 0.6f,0.0f };
		}
		else
		{
			curAction = GLIDE_LEFT;
			spriteMov = { -0.6f,0.0f };
		}
		tickRate = 12;
		break;
	case 0b00000001:
		if (faceRight)
		{
			curAction = MOVE_UP_FACE_RIGHT;
			viewportCatchUpLeft = false;
			viewportCatchUpRight = false;
			stopRight = false;
			stopLeft = false;
			spriteMov = { viewMov.x,-0.8f };
		}
		else
		{
			curAction = MOVE_UP_FACE_LEFT;
			viewportCatchUpLeft = false;
			viewportCatchUpRight = false;
			stopRight = false;
			stopLeft = false;
			spriteMov = { viewMov.x,-0.8f };
		}
		tickRate = 12;
		break;
	case 0b00000010:
		faceRight = false;
		curAction = MOVE_LEFT;
		tickRate = 6;
		spriteMov = { -1.2f,0.0f };
		break;
	case 0b00000100:
		if (faceRight)
		{
			curAction = MOVE_DOWN_FACE_RIGHT;
			viewportCatchUpLeft = false;
			viewportCatchUpRight = false;
			stopRight = false;
			stopLeft = false;
			spriteMov = { viewMov.x,0.8f };
		}
		else
		{
			curAction = MOVE_DOWN_FACE_LEFT;
			viewportCatchUpLeft = false;
			viewportCatchUpRight = false;
			stopRight = false;
			stopLeft = false;
			spriteMov = { viewMov.x,0.8f };
		}
		tickRate = 12;
		break;
	case 0b00001000:
		faceRight = true;
		curAction = MOVE_RIGHT;
		tickRate = 6;
		spriteMov = { 1.2f,0.0f };
		break;
	}
	sprite->move(spriteMov);
	updateView(input);
	if (ticks >= tickRate)
	{
		//reset to 0 so ticks doesn't get to large
		ticks = 0;
		sprite->setTextureRect(*(animations[curAction]->nextFrame()));
	}


}

void Player::updateView(int input)
{
	//std::cout <<"Sprite:"<< sprite->getPosition().x<<' '<< sprite->getPosition().y<< std::endl;
	//std::cout << "viewport:" << viewport->getCenter().x << ' ' << viewport->getCenter().y << std::endl;
	//viewport goes of left end
	if ((viewport->getCenter().x - 125) > 31.f&& (viewport->getCenter().x - 125) < 35.f)
	{
		viewport->setCenter({ 1049.f+((viewport->getCenter().x)-33.f),101.5f});
		sprite->setPosition({ sprite->getPosition().x+1049.f-33.f,sprite->getPosition().y });
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1107.f && (viewport->getCenter().x - 125) < 1111.f)
	{
		//std::cout << "test" << std::endl;
		viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
	}

	if (!(viewportCatchUpLeft)&&(viewport->getCenter().x - 125) >= (sprite->getPosition().x - 45.f))
	{
		leftEdge = true;
		sprite->setPosition({ viewport->getCenter().x - 80.f,sprite->getPosition().y });
	}
	else
		leftEdge = false;

	if (!(viewportCatchUpRight)&&(viewport->getCenter().x + 125) <= ((sprite->getPosition().x+sprite->getGlobalBounds().size.x) + 45.f))
	{
		rightEdge = true;
		sprite->setPosition({ viewport->getCenter().x + 79.f - sprite->getGlobalBounds().size.x, sprite->getPosition().y });
	}
	else
		rightEdge = false;

	if (faceRight)
	{
		if (leftEdge)
		{
			viewMov = { 0.6f, 0.0f };
			viewportCatchUpRight = false;
		}
		else if (rightEdge)
		{
			viewportCatchUpLeft = false;
			viewportCatchUpRight = true;
			stopRight = false;
		}
		else
			viewMov = { 0.8f, 0.0f };
	}
	else
	{
		if (rightEdge)
		{
			viewMov = { -0.6f, 0.0f };
			viewportCatchUpLeft = false;
		}
		else if (leftEdge)
		{
			viewportCatchUpLeft = true;
			viewportCatchUpRight = false;
			stopLeft = false;
		}
		else
			viewMov = { -0.8f, 0.0f };
	}
	if (viewportCatchUpRight && faceRight)
		viewMov = { spriteMov.x * 2,0.0f };
	else if (viewportCatchUpLeft && !faceRight)
		viewMov = { spriteMov.x * 2,0.0f };
	else if (viewportCatchUpRight && !faceRight)
	{
		stopLeft = true;
		viewportCatchUpRight = false;
	}
	else if (viewportCatchUpLeft && faceRight)
	{
		stopRight = true;
		viewportCatchUpLeft = false;
	}
	if (stopRight && !faceRight)
		stopRight = false;
	else if(stopRight&& faceRight)
		viewMov = { 0.1f,0.0f };

	if (stopLeft && faceRight)
		stopLeft = false;
	else if (stopLeft && !faceRight)
		viewMov = { -0.1f,0.0f };


	viewport->move(viewMov);
}


void Player::death()
{

}


void Player::shoot()
{
	//Bullet x(pos);
}

void Player::bomb()
{

}