# pragma once 
#include <SFML/Graphics.hpp>
#include<vector>

class Animation
{
public:
	//when you want to use a set of frames for an animation create an Animation 
	// object and fill in the rows and columns along with the zone of all the frames
	Animation();
	Animation(int row, int col, sf::IntRect zone);
	~Animation();
	sf::IntRect* getFrame(int frame);
	//when frames need to be cycled through call next frame
	sf::IntRect* nextFrame();
	//when cycling frames use this method to set the start frame
	void setFrame(int frame) { curFrame = frame; }
private:
	unsigned int curFrame,frameNum;
	//holds all frames
	std::vector<sf::IntRect> frames;
	int height, width;
	

};