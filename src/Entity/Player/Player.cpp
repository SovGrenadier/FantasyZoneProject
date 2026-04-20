#include"Player.h"
#include<memory>

Player::Player()
{
	set_active = true;
	set_visible = true;
	texture = new sf::Texture("../res/Opa-Opa.png");
	sprite = new sf::Sprite(*texture);
	rightFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{9,37},sf::Vector2i{36,12} });
	leftFly = new Animation(1, 2, sf::IntRect{ sf::Vector2i{69,150},sf::Vector2i{36,12} });
	walkRight = new Animation(1, 2, sf::IntRect{ sf::Vector2i{46,53},sf::Vector2i{36,16} });
	walkLeft = new Animation(1, 2, sf::IntRect{ sf::Vector2i{33,166},sf::Vector2i{36,16} });
	standingRight = new Animation(1, 1, sf::IntRect{ sf::Vector2i{46,53},sf::Vector2i{18,16} });
	standingLeft = new Animation(1, 1, sf::IntRect{ sf::Vector2i{51,166},sf::Vector2i{18,16} });

	animations[Actions::GLIDE_RIGHT] = rightFly;
	animations[Actions::MOVE_RIGHT] = rightFly;
	animations[Actions::MOVE_UP_FACE_RIGHT] = rightFly;
	animations[Actions::MOVE_DOWN_FACE_RIGHT] = rightFly;
	animations[Actions::GLIDE_LEFT] = leftFly;
	animations[Actions::MOVE_LEFT] = leftFly;
	animations[Actions::MOVE_UP_FACE_LEFT] = leftFly;
	animations[Actions::MOVE_DOWN_FACE_LEFT] = leftFly;
	animations[Actions::WALK_RIGHT] = walkRight;
	animations[Actions::WALK_LEFT] = walkLeft;
	animations[Actions::STAND_RIGHT] = standingRight;
	animations[Actions::STAND_LEFT] = standingLeft;

	sprite->setPosition({ 790.f,109.f });
	ceiling.position = { 33.f, 8.f };
	ceiling.size = { 1348.f, 6.f };
	ground.position = { 33.f, 176.f };
	ground.size = { 1348.f , 60.f };
	sprite->setTextureRect(*(animations[curAction]->nextFrame()));

	tickRate = 100000;

}

Player::~Player()
{
	delete texture;
	delete sprite;
	delete rightFly;
	delete leftFly;
	delete walkRight;
	delete walkLeft;
	delete standingRight;
	delete standingLeft;
}

void Player::setHealth()
{
	health = 10000000;
}

//don't try to walk to the left
void Player::update(int input)
{
	if (health <= 0&&alive)
	{
		alive = false;
		ticks = 0;
	}
	if (!alive)
	{
		ticks++;
		std::cout << ticks << std::endl;
		if (ticks >= deathTickCount)
		{
			set_active = false;
		}
		else if(ticks>=40)
			set_visible = false;
	}
	else
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
			//sprite->setPosition({ sprite->getPosition().x, ((ground.position.y)-sprite->getGlobalBounds().size.y-3)});
			hitFloor = true;
		}
		else
			hitFloor = false;

		ticks++;
		//a is pressed
		if (((input % 0b00000100) / 0b00000010) == 1)
			faceRight = false;
		//d is pressed
		if (((input % 0b00010000) / 0b00001000) == 1)
			faceRight = true;

		if (((input % 0b01000000) / 0b00100000) == 1)
		{
			if (bombingTicks >= 36)
			{
				bomb();
				bombingTicks = 0;
			}
			else
				bombingTicks++;
			input -= 0b00100000;
		}
		else if (bombingTicks < 36)
			bombingTicks = 36;


		if (((input % 0b00100000) / 0b00010000) == 1)
		{
			if (shootingTicks >= 6)
			{
				shoot();
				shootingTicks = 0;
			}
			else
				shootingTicks++;
			input -= 0b00010000;
		}
		else if (shootingTicks < 6)
			shootingTicks = 6;


		switch (input)
		{
			//nothing is pressed
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
					curAction = Actions::STAND_RIGHT;
					spriteMov = { 0.0f,0.0f };
				}
				else
				{
					curAction = Actions::STAND_LEFT;
					spriteMov = { 0.0f,0.0f };
				}
				tickRate = 12;
				ticks = 12;
			}
			break;
			//w is pressed
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
			hitFloor = false;
			break;
			//a is pressed
		case 0b00000010:
			faceRight = false;
			if (!hitFloor)
			{
				curAction = Actions::MOVE_LEFT;
				tickRate = 6;
				spriteMov = { -2.2f,0.0f };
			}
			else
			{
				curAction = Actions::WALK_LEFT;
				tickRate = 6;
				spriteMov = { -2.2f,0.0f };
			}
			break;
			//s is pressed
		case 0b00000100:
			if (!hitFloor)
			{
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
			}
			else
			{
				if (faceRight)
				{
					curAction = Actions::STAND_RIGHT;
					spriteMov = { 0.0f,0.0f };
				}
				else
				{
					curAction = Actions::STAND_LEFT;
					spriteMov = { 0.0f,0.0f };
				}
				tickRate = 12;
				ticks = 12;
			}
			break;
			//d is pressed
		case 0b00001000:
			faceRight = true;
			if (!hitFloor)
			{
				curAction = Actions::MOVE_RIGHT;
				tickRate = 6;
				spriteMov = { 2.2f,0.0f };
			}
			else
			{
				curAction = Actions::WALK_RIGHT;
				tickRate = 6;
				spriteMov = { 2.2f,0.0f };
			}
			break;
			//w and d is pressed
		case 0b00001001:
			if (!hitCeil)
			{
				curAction = Actions::MOVE_UP_FACE_RIGHT;
				spriteMov = { 2.2f,-2.0f };
			}
			else
			{
				curAction = Actions::MOVE_RIGHT;
				spriteMov = { 2.2f,0.0f };
			}
			tickRate = 6;
			hitFloor = false;
			faceRight = true;
			break;
			//s and d is pressed
		case 0b00001100:
			if (!hitFloor)
			{
				curAction = Actions::MOVE_DOWN_FACE_RIGHT;
				spriteMov = { 2.2f,2.0f };
			}
			else
			{
				curAction = Actions::WALK_RIGHT;
				spriteMov = { 2.2f,0.0f };
			}
			tickRate = 6;
			faceRight = true;
			break;
			//w and a is pressed
		case 0b00000011:
			if (!hitCeil)
			{
				curAction = Actions::MOVE_UP_FACE_LEFT;
				spriteMov = { -2.2f,-2.0f };
			}
			else
			{
				curAction = Actions::MOVE_LEFT;
				spriteMov = { -2.2f,0.0f };
			}
			tickRate = 6;
			hitFloor = false;
			faceRight = false;
			break;
			//s and a is pressed
		case 0b00000110:
			if (!hitFloor)
			{
				curAction = Actions::MOVE_DOWN_FACE_LEFT;
				spriteMov = { -2.2f,2.0f };
			}
			else
			{
				curAction = Actions::WALK_LEFT;
				spriteMov = { -2.2f,0.0f };
			}
			tickRate = 6;
			faceRight = false;
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
		if (hitFloor)
		{
			sprite->setPosition({ sprite->getPosition().x, ((ground.position.y) - sprite->getGlobalBounds().size.y + 1) });
		}
	}
}


//to-do: Fix viewport catchup after 1 catchup
void Player::updateView(int input)
{
	//std::cout <<"Sprite:"<< sprite->getPosition().x<<' '<< sprite->getPosition().y<< std::endl;
	//std::cout << "viewport:" << viewport->getCenter().x << ' ' << viewport->getCenter().y << std::endl;
	//viewport goes of left end
	if ((viewport->getCenter().x - 125) > 29.f&& (viewport->getCenter().x - 125) < 37.f)
	{
		viewport->setCenter({ 1049.f+((viewport->getCenter().x)-33.f),101.5f});
		sprite->setPosition({ sprite->getPosition().x+1049.f-33.f,sprite->getPosition().y });
		std::cout << "viewport loop1" << std::endl;
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		//std::cout << "test" << std::endl;
		viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
		std::cout << "viewport loop2" << std::endl;
	}
	//player hits the left edge of the viewport
	if (!(viewportCatchUpLeft)&&(viewport->getCenter().x - 125) >= (sprite->getPosition().x - 45.f))
	{
		leftEdge = true;
		sprite->setPosition({ viewport->getCenter().x - 80.f,sprite->getPosition().y });
	}
	else
		leftEdge = false;
	//player hits the right edge of the viewport
	if (!(viewportCatchUpRight)&&(viewport->getCenter().x + 125) <= ((sprite->getPosition().x+sprite->getGlobalBounds().size.x) + 45.f))
	{
		rightEdge = true;
		sprite->setPosition({ viewport->getCenter().x + 80.f - sprite->getGlobalBounds().size.x, sprite->getPosition().y });
	}
	else
		rightEdge = false;
	//to-do: fix viewport when player changes direction during a viewport catchup
	if (faceRight)
	{
		//viewport moves same speed as player
		if (leftEdge)
		{
			viewMov = { spriteMov.x, 0.0f };
			viewportCatchUpRight = false;
		}
		//viewport must catch up and move faster
		else if (rightEdge)
		{
			viewportCatchUpLeft = false;
			viewportCatchUpRight = true;
			stopRight = false;
		}
		//viewport moves faster than player glide slower than player sprint
		else
		{
			viewMov = { 0.8f, 0.0f };
		}
	}
	else
	{
		//viewport moves same speed as player
		if (rightEdge)
		{
			viewMov = { spriteMov.x, 0.0f };
			viewportCatchUpLeft = false;
		}
		//viewport must catch up and move faster
		else if (leftEdge)
		{
			viewportCatchUpLeft = true;
			viewportCatchUpRight = false;
			stopLeft = false;
		}
		//viewport moves faster than player glide slower than player sprint
		else
		{
			viewMov = { -0.8f, 0.0f };
		}
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

//to-do: need to come up with a way to delete bullets when created
void Player::shoot()
{
	if (faceRight)
	{
		//new Bullet({ sprite->getPosition().x + 10,   sprite->getPosition().y + 4 }, faceRight);
		std::shared_ptr<Bullet> bulletDummy = std::make_shared<Bullet>(sf::Vector2f{ sprite->getPosition().x + 10,   sprite->getPosition().y + 4 }, faceRight, slowBullets);
		bulletDummy->initialize();
	}
	else
	{
		std::shared_ptr<Bullet> bulletDummy = std::make_shared<Bullet>(sf::Vector2f{ sprite->getPosition().x,   sprite->getPosition().y + 4 }, faceRight, slowBullets);
		bulletDummy->initialize();
	}
}

void Player::bomb()
{
	if (faceRight)
	{
		std::shared_ptr<Bomb> bombDummy = std::make_shared<Bomb>(sf::Vector2f{ sprite->getPosition().x + 10,   sprite->getPosition().y + 4 }, faceRight);
		bombDummy->initialize();
	}
	else
	{
		std::shared_ptr<Bomb> bombDummy = std::make_shared<Bomb>(sf::Vector2f{ sprite->getPosition().x,   sprite->getPosition().y + 4 }, faceRight);
		bombDummy->initialize();
	}
}