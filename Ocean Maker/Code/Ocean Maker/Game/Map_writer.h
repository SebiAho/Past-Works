#pragma once
#include <string>
#include <fstream>

class Map_writer
{
public:
	Map_writer(void);
	~Map_writer(void);

	void Write_map(std::string string_map[], std::string name, int tile_to_win, int height, int width);
	void Overwrite_map(std::string string_map[], std::string name, int tile_to_win, int height, int width);
	void Delete_map(std::string name, int height, int width);
};

