#include<../../src/Animation/Animation.h>
#include<iostream>

Animation::Animation()
{

}

Animation::Animation(int row, int col, sf::IntRect zone)
{
	curFrame = 0;
	frameNum = row * col;
	sf::Vector2 zoneSize = zone.size;
	sf::Vector2 pos = zone.position;
	int startWidth = pos.x;
	width = zoneSize.x/col;
	height = zoneSize.y/row;
	sf::Vector2 size(width, height);
	sf::IntRect temp;
	temp.size = size;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			temp.position = pos;
			//push all different frames into frames vector
			//we will uses this frames vector for nextFrame and getFrame methods
			frames.push_back(temp);
			pos.x += width;
		}
		pos.y += height;
		pos.x = startWidth;
	}
}

Animation::~Animation()
{

}

sf::IntRect* Animation::getFrame(int frame)
{
	return &frames.at(frame);
}


sf::IntRect* Animation::nextFrame()
{
	curFrame++;
	if (curFrame == frameNum)
	{
		curFrame = 0;
		return &frames.at(frameNum - 1);
	}
	else
		return &frames.at(curFrame - 1);
}