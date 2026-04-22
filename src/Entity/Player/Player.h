#pragma once
#include"../Entity.h"
#include"../../Animation/Animation.h"
#include"../Weapons/Bullet/Bullet.h"
#include"../Weapons/Bomb/Bomb.h"
#include<unordered_map>
#include<iostream>

class Player : public Entity
{
public:
	Player();
	~Player();
	enum class Actions
	{
		GLIDE_LEFT,
		GLIDE_RIGHT,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP_FACE_RIGHT,
		MOVE_UP_FACE_LEFT,
		MOVE_DOWN_FACE_RIGHT,
		MOVE_DOWN_FACE_LEFT,
		WALK_LEFT,
		WALK_RIGHT,
		STAND_LEFT,
		STAND_RIGHT
	};

	void update(int input) override;
	void death() override;
	void setHealth();

	bool slowBullets = false;
	int health;

	std::unordered_map<Actions, Animation*> animations;
private:
	int speed;
	bool faceRight = true;
	Actions curAction = Actions::GLIDE_RIGHT;
	void shoot();
	void bomb();
	void updateView(int input);
	unsigned int tickRate;
	int deathTickCount = 400;
	//represents which level of the background spritesheet the player is on
	int level = 2;
	//represents edges where viewport matches player movement speed
	bool rightEdge = false;
	bool leftEdge = false;
	sf::Vector2f spriteMov;
	sf::Vector2f viewMov;
	sf::FloatRect ceiling;
	sf::FloatRect ground;
	//if player hits an edge of the viewport the viewport speeds up
	bool viewportCatchUpRight = false;
	bool viewportCatchUpLeft = false;
	//When the viewport is catching up, if the player changes direction
	// the viewport stops moving until an edge is hit or the player chenges direction again
	bool stopRight = false;
	bool stopLeft = false;
	bool hitCeil = false;
	bool hitFloor = false;
	//used to store different animations that will go into the map
	Animation* rightFly;
	Animation* leftFly;
	Animation* walkRight;
	Animation* walkLeft;
	Animation* standingRight;
	Animation* standingLeft;
	int shootingTicks = 0;
	int bombingTicks = 0;

};