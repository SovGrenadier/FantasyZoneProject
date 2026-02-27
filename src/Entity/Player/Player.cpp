#include"Player.h"

Player::Player()
{
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	Animation* rightFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{9,37},sf::Vector2i{36,12} });
	Animation* leftFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{69,150},sf::Vector2i{36,12} });
	Animation* walkRight = new Animation(1, 2, sf::IntRect{ sf::Vector2i{46,53},sf::Vector2i{36,16} });
	animations[Actions::GLIDE_RIGHT] = rightFly;
	animations[Actions::MOVE_RIGHT] = rightFly;
	animations[Actions::MOVE_UP_FACE_RIGHT] = rightFly;
	animations[Actions::MOVE_DOWN_FACE_RIGHT] = rightFly;
	animations[Actions::GLIDE_LEFT] = leftFly;
	animations[Actions::MOVE_LEFT] = leftFly;
	animations[Actions::MOVE_UP_FACE_LEFT] = leftFly;
	animations[Actions::MOVE_DOWN_FACE_LEFT] = leftFly;
	animations[Actions::WALK_RIGHT] = walkRight;
	sprite->setPosition({ 790.f,109.f });
	tickRate = 100000;
	ceiling.position = { 33.f, 8.f };
	ceiling.size = { 1348.f, 6.f };
	ground.position = { 33.f, 188.f };
	ground.size = { 1348.f , 6.f };
	sprite->setTextureRect(*(animations[curAction]->nextFrame()));
}

Player::~Player()
{
	delete texture;
	delete sprite;
}


void Player::update(int input)
{
	//check if player hit the ceiling
	if (ceiling.findIntersection(sprite->getGlobalBounds()) != std::nullopt)
	{
		if (!hitCeil)
		{
			sprite->setPosition({ sprite->getPosition().x, (ceiling.position.y + ceiling.size.y - 1) });
			hitCeil = true;
		}
	}
	else
		hitCeil = false;

	//check if player hit the floor
	if (ground.findIntersection(sprite->getGlobalBounds()) != std::nullopt)
	{
		if (!hitFloor)
		{
			sprite->setPosition({ sprite->getPosition().x, ((ground.position.y)-sprite->getGlobalBounds().size.y)});
			hitFloor = true;
		}
	}
	else
		hitFloor = false;


	ticks++;
	//a is pressed
	if (((input % 0b00000100) / 0b00000010) == 1)
		faceRight = false;
	//w is pressed
	if (((input % 0b00010000) / 0b00001000) == 1)
		faceRight = true;
	if (input == 0b00010000)
		shoot();
	switch (input)
	{
	case 0b00000000:
		if (!hitFloor)
		{
			if (faceRight)
			{
				curAction = Actions::GLIDE_RIGHT;
				spriteMov = { 0.6f,0.0f };
			}
			else
			{
				curAction = Actions::GLIDE_LEFT;
				spriteMov = { -0.6f,0.0f };
			}
			tickRate = 12;
		}
		else
		{
			if (faceRight)
			{
				curAction = Actions::STANDING;
				spriteMov = { 0.6f,0.0f };
			}
			else
			{
				curAction = Actions::STANDING;
				spriteMov = { -0.6f,0.0f };
			}
			tickRate = 12;
		}
		break;
	case 0b00000001:
		if (!hitCeil)
		{
			if (faceRight)
			{
				curAction = Actions::MOVE_UP_FACE_RIGHT;
				viewportCatchUpLeft = false;
				viewportCatchUpRight = false;
				stopRight = false;
				stopLeft = false;
				spriteMov = { viewMov.x,-2.0f };
			}
			else
			{
				curAction = Actions::MOVE_UP_FACE_LEFT;
				viewportCatchUpLeft = false;
				viewportCatchUpRight = false;
				stopRight = false;
				stopLeft = false;
				spriteMov = { viewMov.x,-2.0f };
			}
			tickRate = 12;
		}
		else
		{
			if (faceRight)
			{
				curAction = Actions::GLIDE_RIGHT;
				spriteMov = { 0.6f,0.0f };
			}
			else
			{
				curAction = Actions::GLIDE_LEFT;
				spriteMov = { -0.6f,0.0f };
			}
			tickRate = 12;
		}
		break;
	case 0b00000010:
		faceRight = false;
		curAction = Actions::MOVE_LEFT;
		tickRate = 6;
		spriteMov = { -2.2f,0.0f };
		break;
	case 0b00000100:
		if (faceRight)
		{
			curAction = Actions::MOVE_DOWN_FACE_RIGHT;
			viewportCatchUpLeft = false;
			viewportCatchUpRight = false;
			stopRight = false;
			stopLeft = false;
			spriteMov = { viewMov.x,2.0f };
		}
		else
		{
			curAction = Actions::MOVE_DOWN_FACE_LEFT;
			viewportCatchUpLeft = false;
			viewportCatchUpRight = false;
			stopRight = false;
			stopLeft = false;
			spriteMov = { viewMov.x,2.0f };
		}
		tickRate = 12;
		break;
	case 0b00001000:
		faceRight = true;
		curAction = Actions::MOVE_RIGHT;
		tickRate = 6;
		spriteMov = { 2.2f,0.0f };
		break;
	}
	sprite->move(spriteMov);
	updateView(input);
	if (ticks >= tickRate)
	{
		//reset to 0 so ticks doesn't get to large
		ticks = 0;
		if(curAction!=Actions::STANDING)
			sprite->setTextureRect(*(animations[curAction]->nextFrame()));
	}
}

void Player::updateView(int input)
{
	//std::cout <<"Sprite:"<< sprite->getPosition().x<<' '<< sprite->getPosition().y<< std::endl;
	//std::cout << "viewport:" << viewport->getCenter().x << ' ' << viewport->getCenter().y << std::endl;
	//viewport goes of left end
	if ((viewport->getCenter().x - 125) > 29.f&& (viewport->getCenter().x - 125) < 37.f)
	{
		viewport->setCenter({ 1049.f+((viewport->getCenter().x)-33.f),101.5f});
		sprite->setPosition({ sprite->getPosition().x+1049.f-33.f,sprite->getPosition().y });
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
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
		sprite->setPosition({ viewport->getCenter().x + 80.f - sprite->getGlobalBounds().size.x, sprite->getPosition().y });
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