#pragma once
#include <SFML\System\Vector2.hpp>

class Tile
{
public:
	Tile(void);
	Tile(int _value,sf::Vector2f _text);
	Tile(int _value,sf::Vector2f _f1, sf::Vector2f _f2, sf::Vector2f _f3, sf::Vector2f _f4);
	Tile(Tile& tile);

	~Tile(void);
	int value;
	sf::Vector2f texture[4];//Texture locations on the image map
};

class Tile_data
{
public:
	Tile_data(void);
	~Tile_data(void);
	
	void Initialize();

	const Tile& getTile(int _value);
	
private:
	Tile tiles[20];
	
};
