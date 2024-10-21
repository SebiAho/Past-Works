#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Base.h"

class Editor_map_reader
{
public:
	Editor_map_reader(void);
	~Editor_map_reader(void);

	void Read_map(std::string _mapname);//Gets the map from the text file whose name matches the _mapname
	int string_to_int(std::string _s);//converts string value to int

	int getHeight();
	int getWidth();

	std::string string_values[MAX_MAP_HEIGTH];//map values

private:
	int height, width;//map size
};

