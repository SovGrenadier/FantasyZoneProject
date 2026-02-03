#pragma once
#include"../Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	enum Actions
	{
		MOVE_N,
		MOVE_NE,
		MOVE_NW,
		MOVE_E,
		MOVE_W,
		MOVE_S,
		MOVE_SE,
		MOVE_SW,

	};
	//void update() override;
private:



};