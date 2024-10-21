#pragma once
#include <SFML\System\Vector3.hpp>
#include <string>
#include "Base.h"

class Parser
{
public:
	Parser(void);
	~Parser(void);

	sf::Vector3i Parse_to_map(int tile_type);
	void Parse_to_string(int height, int width, std::string string_map[MAX_MAP_HEIGTH], int int_map[MAX_MAP_HEIGTH][MAX_MAP_HEIGTH]);//Parses to string array thats used to save map into file
	sf::Vector3i Parse_from_file(char char_value);//Parses string type map into map arrays
private:
};

