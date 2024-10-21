#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\System\Time.hpp>

#include "Base.h"
#include "Draw_handler.h"
#include "Animation.h"
#include "Tile_data.h"
#include "Map_reader.h"
#include <string>

class Map_handler//Handles the map creation functions
{
public:
	Map_handler(void);
	~Map_handler(void);

	void Initialize(const std::string& _map_name);//Initializes things that need to be initialised everytime a level is loaded
	void Initialize(int _height, int _width);//Intialization used by map editor

	void Draw(Draw_handler& _draw, const float& _deltatime);

	bool Is_Solid(const sf::Vector2f& _pos, float _offsetX, float _offsetY);//Check's if a player can go trought tile/object

	//Getters
	std::string Map_name(){return map_name;};
	sf::Vector2i getMapSize(){ return sf::Vector2i(width*TILESIZE,heigth*TILESIZE); };//Get map size(pixels)
	sf::Vector2f getPlayerStartPos(){ return player_start_pos; };
	int getTilesToWin(){ return tiles_to_win; };

	//Tile/Object getters & setters
	int getTile(int _x, int _y);
	int getTile(sf::Vector2f _pos);

	void setTile(int x, int y, int value);
	void setTile(sf::Vector2f _pos, int value);

	int getObject(int _x, int _y);
	int getObject(sf::Vector2f _pos);

	void setObject(int x, int y, int value);
	void setObject(sf::Vector2f _pos, int value);

private:
	Animation animate;
	Tile_data tile_values;
	Map_reader map_reader;

	int tiles[MAX_MAP_HEIGTH][MAX_MAP_WIDTH], objects[MAX_MAP_HEIGTH][MAX_MAP_WIDTH];
	int width, heigth, tiles_to_win, map_id;
	sf::Vector2f player_start_pos;
	std::string map_name;

	void Parser(std::string _map[MAX_MAP_HEIGTH]);//Goes trough string map thats read from a file and parses it to Tile and Object arrays
	


};

