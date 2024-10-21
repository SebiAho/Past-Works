#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Base.h"

class Map_reader
{
public:
	Map_reader(void);
	~Map_reader(void);

	void Read_map(std::string _mapname);//Gets the map from the text file whose name matches the _mapname
	int string_to_int(std::string _s);//converts string value to int

	int Read_Map_Names(std::vector<std::string>& map_names);//Reads map names from the file and counts the amount of maps
	
	//Getters
	int getHeight();
	int getWidth();
	int getTilesToWin();

	std::string string_values[MAX_MAP_HEIGTH];//map values

private:
	int height, width;//map size
	int tile_to_win;//tiles player must cover to win the level

};

