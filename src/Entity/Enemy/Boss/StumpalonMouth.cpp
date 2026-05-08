#include "StumpalonMouth.h"
#include <iostream>


/// <summary>
/// Creates a mouth object that aligns with the Boss's mouth 
/// </summary>
/// <param name="pos"></param>
StumpalonMouth::StumpalonMouth(sf::Vector2f pos)
{
	//Intialize variables and set health 
	ticks = 24; 
	frame = 0; 
	health = 48;
	set_visible = false;

	//Set up sprite and animation 
	if (!texture->loadFromFile("../res/Bosses.png"))
		std::cout << "Error Loaing from File";
	sprite->setTexture(*texture);
	zone = sf::IntRect(sf::Vector2i{ 213, 33 }, sf::Vector2i{ 18,63});
	changeColor = new Animation{ 3, 2, zone };
	sprite->setTextureRect(*changeColor->getFrame(0));

	//Set the position of the mouth so that it aligns with the Boss's mouth 
	sprite->setPosition(sf::Vector2f{ pos.x+1, pos.y + 34 }); 
}


StumpalonMouth::~StumpalonMouth()
{

}


/// <summary> 
/// changes the visibility of the mouth 
/// </summary> 
/// <param name = "state"></param> 
void StumpalonMouth::setVisibility(bool state)
{
	set_visible = state; 
}


/// <summary> 
/// Changes the color of the mouth by changing its frame. 
/// </summary> 
void StumpalonMouth::changeState()
{
	if (frame == 4)
		frame = 1;
	else
		frame += 2;

	// determines if the current frame is in the zone. 
	// if not, it sets the frame to the final one that is outside the zone
	if(frame<=5)
		sprite->setTextureRect(*changeColor->getFrame(frame));
	else
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(231, 54), sf::Vector2i(12, 23)));
}


/// <summary>
/// Initaites the move function.
/// </summary>
/// <param name = "input"></param> 
void StumpalonMouth::update(int input)
{
	ticks++; 
	move(); 
}


/// <summary>
/// Ensures the sprite loops with the viewport and updates the position of the sprite. 
/// </summary>
void StumpalonMouth::move()
{
	//Ensures sprite doesn't disappear when the viewport loops
	if ((viewport->getCenter().x - 125) > 29.f && (viewport->getCenter().x - 125) < 37.f)
	{
		//handled through player
		//viewport->setCenter({ 1049.f + ((viewport->getCenter().x) - 33.f),101.5f });
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 1049.f - 33.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}
	//viewport goes off right end
	if ((viewport->getCenter().x - 125) > 1105.f && (viewport->getCenter().x - 125) < 1113.f)
	{
		viewportLoop = true;
		sprite->setPosition({ sprite->getPosition().x + 93.f - 1109.f,sprite->getPosition().y });
		pos = sprite->getPosition();
	}

	//Calculate the y speed give the the time since creation of the mouth (ticks) 
	float ySpeed;
	ySpeed = -sin((ticks * PI) / 100);

	sprite->move(sf::Vector2f(.7f, ySpeed));
}


/// <summary>
/// Updates health based on collision damage, and changes the color of the mouth based on health. 
/// </summary> 
/// <param name = "damage"></param> 
void StumpalonMouth::takeDamage(int damage)
{
	health -= damage; 

	if (health == 36)
		set_visible = true;
	else if (health % 6 == 0)
		changeState();
		
}


/// <summary>
/// Updates the state of the mouth upon death
/// </summary>
void StumpalonMouth::death()
{
	set_active = false;
	alive = false; 
}
