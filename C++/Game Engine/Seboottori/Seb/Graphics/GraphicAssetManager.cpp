#include "GraphicAssetManager.h"
#include <iostream>
#include "..\System\Definitions.h"

using namespace seb;
GraphicAssetManager::GraphicAssetManager()
{
}


GraphicAssetManager::~GraphicAssetManager()
{
}

int GraphicAssetManager::LoadTexture(std::string _filename, sf::IntRect _area)
{
	//Check if image is already loaded
	if (texture_map.empty() == false)
	{
		if (texture_map.count(_filename) != 0)
			return 2;
	}

	sf::Texture temp;
	if (temp.loadFromFile(ASSET_PATH+_filename, _area) == true)
	{
		texture_map.insert(std::pair<std::string,sf::Texture>(_filename, temp));
		return 1;
	}

	return -1;
}

sf::Texture& GraphicAssetManager::getTexture(std::string _texture)
{
	try
	{
		if (texture_map.find(_texture) != texture_map.end())
			return texture_map[_texture];
		else
			throw -1;
	}
	catch (int e)
	{
		std::cout << e << "Texture of name " << _texture << " could not be found" << std::endl;
	}
}