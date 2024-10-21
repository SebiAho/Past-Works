#include "Tile_data.h"


Tile_data::Tile_data(void)
{
}


Tile_data::~Tile_data(void)
{
}

void Tile_data::Initialize()
{
	//Transparent (default initialization)
	tiles[0] = Tile(0,sf::Vector2f(0,0));

	//Transparent (solid))
	tiles[1] = Tile(1,sf::Vector2f(0,0));

	//Grass
	tiles[2] = Tile(2,sf::Vector2f(0,100));

	//Stone floor
	tiles[3] = Tile(3,sf::Vector2f(100,100));

	//Water
	tiles[4] = Tile(4,sf::Vector2f(0,200),sf::Vector2f(200,200),sf::Vector2f(200,200),sf::Vector2f(0,200));

	//Lava
	tiles[5] = Tile(5,sf::Vector2f(200,300),sf::Vector2f(100,300),sf::Vector2f(100,300),sf::Vector2f(200,300));

	//Ice
	tiles[6] = Tile(6,sf::Vector2f(0,600), sf::Vector2f(0,600), sf::Vector2f(0,500), sf::Vector2f(0,500));

	//Red Ice
	tiles[7] = Tile(7,sf::Vector2f(100,400));

	//Pyramid
	tiles[8] = Tile(8,sf::Vector2f(300,100));

	//Mirror Ice
	tiles[9] = Tile(9,sf::Vector2f(100,500));

	//Dirt
	tiles[10] = Tile(10,sf::Vector2f(200,100));

	//Rock
	tiles[11] = Tile(11,sf::Vector2f(300,500));

	//Ghost Grave
	tiles[12] = Tile(12,sf::Vector2f(200,500));

	//Ghost
	tiles[13] = Tile(13,sf::Vector2f(200,400), sf::Vector2f(200,400), sf::Vector2f(300,400), sf::Vector2f(300,400));

	//Wall Front
	tiles[14] = Tile(14,sf::Vector2f(100,700));

	//Wall Top
	tiles[15] = Tile(15,sf::Vector2f(100,600));

	//Sand
	tiles[16] = Tile(16,sf::Vector2f(200,600));

	//Player
	tiles[17] = Tile(17,sf::Vector2f(300,600));

}

const  Tile& Tile_data::getTile(int _value)
{
		return tiles[_value];
}

//Tile
Tile::Tile(void):value(0),texture()
{
	
}
Tile::Tile(int _value,sf::Vector2f _text):value(_value)
{
	texture[0] = texture[1] = texture[2] = texture[3] =_text;
}

Tile::Tile(int _value,sf::Vector2f _f1, sf::Vector2f _f2, sf::Vector2f _f3, sf::Vector2f _f4):value(_value)
{
		texture[0] = _f1;
		texture[1] = _f2;
		texture[2] = _f3;
		texture[3] = _f4;
}

Tile::Tile(Tile& _tile):value(_tile.value)
{
	for(int i = 0; i < 4; i++)
	{
		texture[i] = _tile.texture[i];
	}
}

Tile::~Tile(void)
{

}