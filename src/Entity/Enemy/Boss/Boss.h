#include "../Enemy.h"


class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	void attack() override;
	void death() override;
	void move() override; 
	void update(int) override;

private:
	int ticks; 
	Animation* glideRight; 
};