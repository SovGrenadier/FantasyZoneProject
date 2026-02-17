#pragma once
#include "../Enemy.h"
#include "../../../Animation/Animation.h"

//orange guy
//made up of groups that are together in a column but move in sync
class Moocolon : public Enemy
{
public:
	Moocolon();
	~Moocolon();

	void spawn() override;
	void move() override;
private:

};