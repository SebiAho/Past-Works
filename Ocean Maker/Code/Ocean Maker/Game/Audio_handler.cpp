#include "Audio_handler.h"


Audio_handler::Audio_handler(void)
{
}


Audio_handler::~Audio_handler(void)
{
}

int Audio_handler::Load_sound_files()
{
	int files_loaded = 0;
	
	if(lava.loadFromFile("Resources/Audio/flamestrike.wav"))
	{
		files_loaded++;
	}
	
	if(ice.loadFromFile("Resources/Audio/IceSlide.wav"))
	{
		files_loaded++;
	}
	
	if(ghost.loadFromFile("Resources/Audio/Ghost.wav"))
	{
		files_loaded++;
	}

	if(water.loadFromFile("Resources/Audio/Water.wav"))
	{
		files_loaded++;
	}

	return files_loaded;
}

void Audio_handler::Play(char _sound)
{
	
	sound.setVolume(100);
	if(_sound == 'L')
	{
		sound.setBuffer(lava);
	}
	else if(_sound == 'I')
	{
		sound.setBuffer(ice);
	}
	else if(_sound == 'G')
	{
		sound.setBuffer(ghost);
		sound.setVolume(20);
	}
	else if(_sound == 'W')
	{
		sound.setBuffer(water);
	}
	
	sound.play();
}

bool Audio_handler::isPlaying()
{
	if(sound.getStatus() == sf::SoundSource::Playing)
	{
		return true;
	}
	return false;
}
