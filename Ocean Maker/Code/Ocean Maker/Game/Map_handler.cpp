#include "Map_handler.h"



Map_handler::Map_handler(void)
{
	for(int y = 0; y < MAX_MAP_HEIGTH; y++)//Init arrays to 0
	{
		for(int x = 0; x < MAX_MAP_WIDTH; x++)
		{
			tiles[y][x] = 0;
			objects[y][x] = 0;
		}
	}
}


Map_handler::~Map_handler(void)
{
}

void Map_handler::Initialize(const std::string& _map_name)//Initializes things that need to be initialised everytime a level is loaded
{
	for(int y = 0; y < MAX_MAP_HEIGTH; y++)//Init arrays to 0
	{
		for(int x = 0; x < MAX_MAP_WIDTH; x++)
		{
			tiles[y][x] = 0;
			objects[y][x] = 0;
		}
	}
	tile_values.Initialize();
	animate = Animation(4,0.2f);
	//Get level data

	map_name = _map_name;
	map_reader.Read_map(map_name);

	//Set the map size & tiles to win
	heigth = map_reader.getHeight();
	width = map_reader.getWidth();
	tiles_to_win = map_reader.getTilesToWin();

	//Other initializations
	player_start_pos.x = 0; player_start_pos.y = 0; //Set playerstart pos default value
	Parser(map_reader.string_values);
}

void Map_handler::Initialize(int _height, int _width)//Intialization used by map editor
{
	for(int y = 0; y < MAX_MAP_HEIGTH; y++)//Init arrays to 0
	{
		for(int x = 0; x < MAX_MAP_WIDTH; x++)
		{
			tiles[y][x] = 0;
			objects[y][x] = 0;
		}
	}
	tile_values.Initialize();
	animate = Animation(4,0.2f);

	//Set the map size & tiles to win
	heigth = _height;
	width = _width;
	tiles_to_win = 200;

	//Other initializations
	Parser(map_reader.string_values);
}



void Map_handler::Parser(std::string _map[20])//Goes trough string map thats read from a file and parses it to Tile and Object arrays
{
	

	for(int y = 0; y < heigth; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(_map[y][x] == '0')//Transparent
			{
				tiles[y][x] = 0;
				objects[y][x] = 0;
			}

			else if(_map[y][x] == '#')//Transparent (solid)
			{
				tiles[y][x] = 0;
				objects[y][x] = 1;
			}

			if(_map[y][x] == '.')//Grass
			{
				tiles[y][x] = 2;
				objects[y][x] = 0;
			}

			if(_map[y][x] == '-')//Stone floor
			{
				tiles[y][x] = 3;
				objects[y][x] = 0;
			}

			if(_map[y][x] == ',')//Dirt
			{
				tiles[y][x] = 10;
				objects[y][x] = 0;
			}

			if(_map[y][x] == 's')//Sand
			{
				tiles[y][x] = 16;
				objects[y][x] = 16;
			}

			if(_map[y][x] == '1')//Rock Grass
			{
				tiles[y][x] = 2;
				objects[y][x] = 11;
			}

			if(_map[y][x] == '2')//Rock Stone
			{
				tiles[y][x] = 3;
				objects[y][x] = 11;
			}

			if(_map[y][x] == '3')//Rock Dirt
			{
				tiles[y][x] = 10;
				objects[y][x] = 11;
			}

			if(_map[y][x] == '4')//Rock Sand
			{
				tiles[y][x] = 16;
				objects[y][x] = 11;
			}

			if(_map[y][x] == '5')//Pyramid Grass
			{
				tiles[y][x] = 2;
				objects[y][x] = 8;
			}

			if(_map[y][x] == '6')//Pyramid Stone
			{
				tiles[y][x] = 3;
				objects[y][x] = 8;
			}
		
			if(_map[y][x] == '7')//Pyramid Dirt
			{
				tiles[y][x] = 10;
				objects[y][x] = 8;
			}

			if(_map[y][x] == '8')//Pyramid Sand
			{
				tiles[y][x] = 16;
				objects[y][x] = 8;
			}

			if(_map[y][x] == 'F')//Wall front
			{
				tiles[y][x] = 0;
				objects[y][x] = 14;
			}

			if(_map[y][x] == 'f')//Wall Top
			{
				tiles[y][x] = 0;
				objects[y][x] = 15;
			}

			if(_map[y][x] == 'w')//Water
			{
				tiles[y][x] = 4;
				objects[y][x] = 0;
			}

			if(_map[y][x] == 'L')//Lava
			{
				tiles[y][x] = 5;
				objects[y][x] = 0;
			}

			if(_map[y][x] == 'I')//Ice
			{
				tiles[y][x] = 6;
				objects[y][x] = 0;
			}

			if(_map[y][x] == 'i')//Red Ice
			{
				tiles[y][x] = 7;
				objects[y][x] = 0;
			}			

			if(_map[y][x] == 'g')//Ghost Transparent
			{
				tiles[y][x] = 12;
				objects[y][x] = 0;
			}

			if(_map[y][x] == 'G')//Ghost
			{
				tiles[y][x] = 12;
				objects[y][x] = 13;
			}

			if(_map[y][x] == 'M')//Mirror ice
			{
				tiles[y][x] = 9;
				objects[y][x] = 0;
			}

			if(_map[y][x] == 'P')//Player starting location
			{
				tiles[y][x] = 17;
				objects[y][x] = 0;
				player_start_pos.y = y*TILESIZE;
				player_start_pos.x = x*TILESIZE;
			}
		}
	}
}

void Map_handler::Draw(Draw_handler& _draw, const float& _deltatime)
{
	animate.Update(_deltatime);

	for(int y = 0; y < heigth; y++)
	{
		for(int x = 0; x < width; x++)
		{
			_draw.Rectangle(sf::Vector2f(x*TILESIZE,y*TILESIZE),tile_values.getTile(tiles[y][x]).texture[animate.getIndex()]);
			_draw.Rectangle(sf::Vector2f(x*TILESIZE,y*TILESIZE),tile_values.getTile(objects[y][x]).texture[animate.getIndex()]);
		}
	}
}

bool Map_handler::Is_Solid(const sf::Vector2f& _pos, float _offsetY,float _offsetX)//Check's if a player can go trought tile/object
{
	if(getObject(_pos.x +_offsetX, _pos.y + _offsetY) == 1 || getTile((int)_pos.x +_offsetX, _pos.y + _offsetY) == 4
		|| getObject(_pos.x +_offsetX, _pos.y + _offsetY) == 8	|| getObject(_pos.x +_offsetX, _pos.y + _offsetY) == 11
		|| getObject(_pos.x +_offsetX, _pos.y + _offsetY) == 13 || getObject(_pos.x +_offsetX, _pos.y + _offsetY) == 14
		|| getObject(_pos.x +_offsetX, _pos.y + _offsetY) == 15)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Tile getters_______________________________________
int Map_handler::getTile(int _x, int _y)
{
	return tiles[_y/TILESIZE][_x/TILESIZE];
}

int Map_handler::getTile(sf::Vector2f _pos)
{
	return tiles[(int)_pos.y/TILESIZE][(int)_pos.x/TILESIZE];
}
//Tile setters_______________________________________
void Map_handler::setTile(int _x, int _y, int value)
{
	tiles[_y/TILESIZE][_x/TILESIZE] = value;
}

void Map_handler::setTile(sf::Vector2f _pos, int value)
{
	tiles[(int)_pos.y/TILESIZE][(int)_pos.x/TILESIZE] = value;
}
//Object getters_____________________________________
int Map_handler::getObject(int _x, int _y)
{
	return objects[_y/TILESIZE][_x/TILESIZE];
}

int Map_handler::getObject(sf::Vector2f _pos)
{
	return objects[(int)_pos.y/TILESIZE][(int)_pos.x/TILESIZE];
}
//Object setters_____________________________________
void Map_handler::setObject(int _x, int _y, int value)
{
	objects[_y/TILESIZE][_x/TILESIZE] = value;
}

void Map_handler::setObject(sf::Vector2f _pos, int value)
{
	objects[(int)_pos.y/TILESIZE][(int)_pos.x/TILESIZE] = value;
}