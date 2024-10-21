#pragma once
#include <string>

#include "Draw_handler.h"
#include "Tile_data.h"
#include "Base.h"

#include "Editor_camera.h"
#include "Parser.h"

#include <SFML\Graphics.hpp>

class Edit_map
{
public:
	Edit_map(sf::RenderWindow& _window);
	~Edit_map(void);

	void Update(Draw_handler& _draw, int& editor_state, const int& _mouseWheel, bool& e_save);//Upates the editor and draws the map
	void Initialize(std::string _name, int _height, int _width);//Initialization for new level
	void Initialize(std::string _name);//Initialization for existing level
	void Delete_map(std::string _name);
	std::string getName(){return name;};

private:
	std::string name;
	int height, width, selected_object, selected_tile, mouse_wheel;
	std::string string_map[MAX_MAP_HEIGTH];

	sf::RenderWindow& window;
	int tiles[MAX_MAP_HEIGTH][MAX_MAP_WIDTH], objects[MAX_MAP_HEIGTH][MAX_MAP_WIDTH], int_map[MAX_MAP_HEIGTH][MAX_MAP_WIDTH];//Values of map locations
	bool tiles_to_change[MAX_MAP_HEIGTH][MAX_MAP_WIDTH];//Tiles player needs to change to win the level
	int tiles_to_win;
	bool gridOn, TilesToChangeOn, owerWrite, change_all;

	sf::Vector2f viewPos;
	sf::Vector2i  mousePos;
	Tile_data tile_values;
	Editor_camera *camera;
	Parser parser;

	void Tile_placement();//Contains code involved in tile placement
	void Save_new_map();//Saves the map into the end of file
	void Save_old_map();//Saves the map over an existing map
};

