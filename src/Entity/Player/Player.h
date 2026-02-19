#pragma once
#include"../Entity.h"
#include"../../Animation/Animation.h"
#include"../Weapons/Bullet/Bullet.h"
#include<unordered_map>
#include<iostream>

class Player : public Entity
{
public:
	Player();
	~Player();
	void getView(sf::View* view) { viewport = view; }
	enum Actions
	{
		GLIDE_LEFT,
		GLIDE_RIGHT,
		MOVE_LEFT,
		MOVE_RIGHT,
	};

	void update(int input) override;
	void death() override;

	std::unordered_map<Actions, Animation*> animations;
private:
	int speed;
	bool faceRight = true;
	Actions curAction = GLIDE_RIGHT;
	sf::View* viewport;
	void shoot();
	void updateView(int input);
	unsigned int tickRate;
	//represents which level of the background spritesheet the player is on
	int level = 2;

};