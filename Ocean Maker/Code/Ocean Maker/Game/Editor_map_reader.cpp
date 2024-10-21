#include "Editor_map_reader.h"
#include <sstream>

Editor_map_reader::Editor_map_reader(void)
{
}


Editor_map_reader::~Editor_map_reader(void)
{
}

void Editor_map_reader::Read_map(std::string _map)
{
	for(int i = 0; i < MAX_MAP_WIDTH; i++)//Initialize array
		string_values[i] = "";

	std::string line;
	std::ifstream file;
	file.open("Resources/map_file.txt", std::ios::in);
	if(file.is_open())
	{
		bool close = false;
		while(close == false && !file.eof())
		{
			std::getline (file,line);
			if(line == _map)
			{
				std::getline (file,line);
				height = string_to_int(line);//Get map height
				std::getline (file,line);
				
				for(int i = 0; i < height; i++)//Get map tiles
				{
					std::getline (file,line);
					string_values[i] = line;
				}
				width = string_values[1].size();//get map width

				close = true;
			}

		}
	}
	file.close();

}

int Editor_map_reader::string_to_int(std::string _s)//Convert string number to int
{
	int value;
	std::stringstream convert_stream(_s);
	
	if(!(convert_stream >> value))//Set the value to the variaple anf check for errors
	{
		value = 0;
	}

	return value;
}

int Editor_map_reader::getHeight()
{
	return height;
}

int Editor_map_reader::getWidth()
{
	return width;
}