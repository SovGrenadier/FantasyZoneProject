#include "Boss.h"
#include<iostream>
#include <time.h>


/// <summary>
/// Creates a boss object relative to the player's position
/// </summary>
/// <param name="playerPos"></param>
Boss::Boss(float playerXPos)
{ 
	ticks = 24; 

	// Set up sprite 
	if (!texture->loadFromFile("../res/Bosses.png"))
		std::cout << "Error Loaing from File"; 

	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect{ sf::Vector2i(11,14), sf::Vector2i(62,79) });
	
	glideRight = new Animation(1, 3, 
		sf::IntRect{ sf::Vector2i(8,14), sf::Vector2i(200,79) });

	// Initialize the Boss's position based on the player's 
	sprite->setPosition(sf::Vector2f(playerXPos + 80.f, 75.f));
}


Boss::~Boss()
{

}


/// <summary>
/// Creates a randomized number of leafs to eject from the Boss's mouth when it is 
/// Open. 
/// </summary>
void Boss::attack()
{
	int leafs; 
	leafs = rand() % 5 +1; 
	for(int i=0 ; i<leafs; i++)
		std::make_shared<Leaf>(sf::Vector2f{ sprite->getPosition().x,
			sprite->getPosition().y + 39 })->initialize();
}


/// <summary>
/// Updates the state of the boss once it dies 
/// </summary>
void Boss::death()
{
	alive = false;
	set_active = false;
}


/// <summary>
/// Changes the location of the Boss so that it resembles a sinusoidal function, and 
/// ensures the Boss loops with the viewport 
/// </summary>
void Boss :: move()
{
	//Ensures sprite doesn't disappear when the viewport loops
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		//handled through player
		//std::cout << "test" << std::endl;
		//viewport->setCenter({ 93.f + ((viewport->getCenter().x) - 1109.f),101.5f });
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
	}

	//Calculate the change in y position of the boss given the time since creation (ticks)
	float ySpeed;
	ySpeed =  - sin((ticks * PI) / 100);

	sprite->move(sf::Vector2f(.7f, ySpeed ));
}


/// <summary>
/// Animates the Boss's mouth movement, initiates death once the Boss's health 
/// reaches 0, triggers move and attack functions, and controls the visibility of the 
/// mouth piece. 
/// </summary>
/// <param name="input"></param>
void Boss::update(int input)
{
	//creates the mouth for the boss when it is created 
	if (ticks == 24)
	{
		mouth = std::make_shared<StumpalonMouth>(sprite->getPosition());
		mouth->initialize();
	}

	//Iniitiate the death for boss and mouth once the health of the mouth reaches 0
	if (mouth->getHealth() == 0)
	{
		mouth->death();
		death();
	}

	move();

	// Animate the boss, but not in typical pattern. 
	if (ticks % 50 == 0)
	{
		if (frame == OPEN_MOUTH)
		{
			openning = false; 
			sprite->setTextureRect(*glideRight->getFrame(OPEN_MOUTH));
			frame--;
		}
		else if (frame == CLOSED_MOUTH)
		{
			openning = true;
			sprite->setTextureRect(*glideRight->getFrame(CLOSED_MOUTH));
			frame++;
		}
		else if (frame==AJAR_MOUTH)
		{
			sprite->setTextureRect(*glideRight->getFrame(AJAR_MOUTH));

			if (openning)
				frame++;
			else
				frame--; 
		}
	}

	// Attack When the mouth is open
	if (sprite->getTextureRect() == *glideRight->getFrame(OPEN_MOUTH) && ticks % 7 == 0) 
		attack();

	// Set the mouthpiece invisible when the mouth is open since it only shows a closed mouth
	if (sprite->getTextureRect() == *glideRight->getFrame(CLOSED_MOUTH) && mouth->getHealth() <= 42)
		mouth->setVisibility(true);
	else
		mouth->setVisibility(false);

	ticks++;
}


/// <summary>
/// returns the health of the mouth of boss since that is the only place it can take damage. 
/// </summary>
/// <return></return>
int Boss :: getHealth()
{
	if (mouth == nullptr)
		return 1000;
	else
		return mouth->getHealth();
}
