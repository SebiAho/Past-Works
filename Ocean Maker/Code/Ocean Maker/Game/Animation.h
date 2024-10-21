#pragma once
#include <SFML\System\Time.hpp>

class Animation//Class that handles the changing of animation frame
{
public:
	Animation();
	Animation(const int _frames, const float _updateInterval);
	~Animation(void);

	void Update(const float& _deltaTime);//Change animation frames
	int getIndex();

private:
	int index, frames;
	float frameTime, updateInterval;
};

