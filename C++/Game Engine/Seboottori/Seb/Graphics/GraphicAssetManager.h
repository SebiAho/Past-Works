#pragma once
#include <unordered_map>
#include <string>

#include "../3rd_party/SFML/SFML/Graphics/Texture.hpp"
#include "../3rd_party/SFML/SFML/Graphics/Rect.hpp"

namespace seb
{
	class GraphicAssetManager//Manages load and storage of graphic assets like textures and fonts
	{
	public:
		GraphicAssetManager();
		~GraphicAssetManager();

		/*Loads texture from Assets folder and stores it into texture_map, 
			_filename = name and index of the loaded image (Note! no file path), 
			_area = what part of the image is loaded (load's whole image by default),
			returns 1 on success, 2 if texture is alredy loaded and -1 on failure*/
		int LoadTexture(std::string _filename, sf::IntRect _area = sf::IntRect());
		
		sf::Texture& getTexture(std::string _texture);

	private:
		std::unordered_map<std::string, sf::Texture> texture_map;

	};
}

