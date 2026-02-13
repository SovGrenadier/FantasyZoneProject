#include "../Enemy.h"


class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	void attack() override;
	void death() override;
private:

};