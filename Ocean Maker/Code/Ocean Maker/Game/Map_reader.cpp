#include "Map_reader.h"
#include <sstream>

Map_reader::Map_reader(void)
{
}


Map_reader::~Map_reader(void)
{
}

void Map_reader::Read_map(std::string _map)//Gets the map from the text file whose name matches the _mapname
{
	for(int i = 0; i < MAX_MAP_WIDTH; i++)//Initialize array
		string_values[i] = "";

	std::string line;
	std::ifstream file;
	file.open("Resources/map_file.txt", std::ios::in);
	if(file.is_open())
	{
		bool close = false;
		while(close == false || !file.eof())
		{
			std::getline (file,line);
			if(line == _map)
			{
				std::getline (file,line);
				height = string_to_int(line);//Get map height
				
				std::getline (file,line);
				tile_to_win = string_to_int(line);//Get tiles required to win the map
				
				for(int i = 1; i < height+2; i++)//Get map tiles
				{
					std::getline (file,line);
					string_values[i] = '#' + line + '#';
				}
				width = string_values[1].size();;//get map width

				for(int i = 0; i < width; i++)//Place top and bottom map borders
				{
					string_values[0] += '#';
					string_values[height+1] += '#';
					//If array location is not correct it may cause problems!!!
				}
				close = true;
			}

		}
	}
	file.close();

}

int Map_reader::Read_Map_Names(std::vector<std::string>& map_names)//Reads map names from the file and counts the amount of maps
{
	int map_amount = 0;
	std::string line;
	std::ifstream file;
	file.open("Resources/map_file.txt", std::ios::in);
	if(file.is_open())
	{
		while(!file.eof())
		{
			std::getline (file,line);
			if(line == "#level#")
			{
				std::getline (file,line);
				map_names.push_back(line);//Get map name
				map_amount++;
			}
		}
	}
	file.close();

	return map_amount;
}

int Map_reader::string_to_int(std::string _s)//Convert string number to int
{
	int value;
	std::stringstream convert_stream(_s);
	
	if(!(convert_stream >> value))//Set the value to the variaple anf check for errors
	{
		value = 0;
	}

	return value;
}

//Getters
int Map_reader::getHeight()
{
	return height+2;
}

int Map_reader::getWidth()
{
	return width;
}

int Map_reader::getTilesToWin()
{
	return tile_to_win;
}