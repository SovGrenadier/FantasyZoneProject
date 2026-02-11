#pragma once
#include"../Entity.h"
#include"../../Animation/Animation.h"
#include<unordered_map>

class Player : public Entity
{
public:
	Player();
	~Player();
	void update(int input);
	void getView(sf::View* view) { viewport = view; }
	enum Actions
	{
		GLIDE_LEFT,
		GLIDE_RIGHT,
		MOVE_LEFT,
		MOVE_RIGHT,
	};
	//void update() override;
	std::unordered_map<Actions, Animation*> animations;
private:
	int speed;
	bool faceRight = true;
	Actions curAction = GLIDE_RIGHT;
	sf::View* viewport;
	void updateView();


};