#pragma once
#include "../Entity.h"


class Shop : public Entity
{
public:
	Shop();
	~Shop();
	void update(int input) override;
private:

};