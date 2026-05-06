#include<../../src/Animation/Animation.h>
#include<iostream>



Animation::Animation()
{

}


/// <summary>
/// Creates an animation objects that breaks up a zone into the specified amount of
/// rows and columns.
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
/// <param name="zone"></param>
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


/// <summary>
/// Returns a specific frame in the animation specified in the parameter
/// </summary>
/// <param name="frame"></param>
/// <returns></returns>
sf::IntRect* Animation::getFrame(int frame)
{
	return &frames.at(frame);
}


/// <summary>
/// Returns the next frame it the sequence, if you call this function over and over
/// you will cyucle through the frames for your given animation.
/// </summary>
/// <param name="frame"></param>
/// <returns></returns>
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


/// <summary>
/// Alllows you to add a frame to the animation sequence
/// </summary>
/// <param name="frame"></param>
void Animation::addFrame(const sf::IntRect& frame)
{
	frames.push_back(frame);
	frameNum = frames.size();
}