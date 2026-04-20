#pragma once
#include "../Enemy.h"
#include "../../../Animation/Animation.h"
#include <unordered_map>


class Bottaco : public Enemy
{
public:
	Bottaco(sf::Vector2f pos);
	~Bottaco();
	        
	enum Actions
	{
		FLY,
		DEATH
	};

	void move() override;
	void update(int) override;
	void death() override;

	sf::Sprite* getSprite() { return sprite; }
	std::unordered_map<Actions, Animation*> animations;
private:
	Actions curAction;
	bool faceRight;
	float centerX, centerY;
	float amplitudeX, amplitudeY;
	float time;
};