#include<../../src/Animation/Animation.h>

Animation::Animation(int row, int col, sf::IntRect zone)
{
	curFrame = 0;
	frameNum = row * col;
	sf::Vector2 zoneSize = zone.size;
	sf::Vector2 pos = zone.position;
	int startWidth = pos.x;
	width = zoneSize.x;
	height = zoneSize.y;
	sf::Vector2 size(width, height);
	sf::IntRect temp;
	temp.size = size;
	for (int i = 0; i < col; i++)
	{
		if (i > 0)
			pos.y += height;
		for (int j = 0; j < row; j++)
		{
			if (i > 0)
				pos.x += width;
			temp.position = pos;
			frames.push_back(temp);
		}
		pos.x = startWidth;
	}
}

Animation::~Animation()
{

}

sf::IntRect Animation::getFrame(int frame)
{
	return frames.at(frame);
}


sf::IntRect Animation::nextFrame()
{
	curFrame++;
	if (curFrame == frameNum)
	{
		curFrame = 0;
		return frames.at(frameNum - 1);
	}
	else
		return frames.at(curFrame - 1);
}