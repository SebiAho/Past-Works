#pragma once
#include <SFML\Audio.hpp>
#include <vector>

class Audio_handler
{
public:
	Audio_handler(void);
	~Audio_handler(void);

	int Load_sound_files();

	void Play(char _sound);
	bool isPlaying();
private:
	sf::SoundBuffer lava, ice, ghost, water;
	sf::Sound sound;

};

