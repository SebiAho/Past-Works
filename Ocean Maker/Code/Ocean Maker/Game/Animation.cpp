#include "Animation.h"
#include <iostream>

Animation::Animation():index(0),frameTime(0)
{
}

Animation::Animation(const int _frames, const float _updateInterval) : index(0), frameTime(0.0f), frames(_frames), updateInterval(_updateInterval)
{
}


Animation::~Animation(void)
{
}

void Animation::Update(const float& _deltaTime)//Change animation frame
{
	frameTime += _deltaTime;
	if(frameTime >= updateInterval)//Check if time bassed is more or equal than updateInterval
	{
		frameTime = 0.0f;
		index++;//Change animation frame
	
		if(index >= frames)
		{
			index = 0;
		}
	}
}

int Animation::getIndex()
{
	return index;
}