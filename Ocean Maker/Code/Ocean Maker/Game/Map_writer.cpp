#include "Map_writer.h"
#include <vector>

Map_writer::Map_writer(void)
{
}


Map_writer::~Map_writer(void)
{
}

void Map_writer::Write_map(std::string string_map[], std::string name, int tile_to_win, int height, int width)
{
	std::string line;
	std::ofstream file;
	file.open("Resources/map_file.txt", std::ios::out|std::ios::app);

	if(file.is_open())
	{
		file <<"\n";
		file << "#level#" << "\n";
		file << name << "\n";
		file << height << "\n";
		file << tile_to_win << "\n";
		for(int y = 0; y < height; y++)
		{
			file << string_map[y] << "\n";
		}
		file.close();
	}

}

void Map_writer::Overwrite_map(std::string string_map[], std::string name, int tile_to_win, int height, int width)
{
	std::string line;
	std::fstream file;
	std::vector<std::string> temp_b, temp_a;//Temporary vectors for holding the file data that comes before and after the edited map
	bool before_map = true;

	//Save the text file to temp_b and temp_a vectors
	file.open("Resources/map_file.txt", std::ios::in);
	if(file.is_open())
	{
		while(!file.eof())
		{
			std::getline (file,line);
			if(before_map == true)//Save the parts of file that come before the edited map into tem_b
			{
				if(line != name)//Copy till edited map
				{
					temp_b.push_back(line);
				}
				else//Advance read location over the edited file
				{
					std::getline (file,line);
					std::getline (file,line);
					for(int y = 0; y < height; y++)
					{
						std::getline (file,line);
					}
					before_map = false;
				}
			}
			else//Save the parts of file that come after the edited map into tem_a
			{
				temp_a.push_back(line);
			}
		}
		file.close();
	}

	file.open("Resources/map_file.txt", std::ios::out | std::ios::trunc);
	if(file.is_open())
	{
		//Write the temp_b vector into file
		for(int i = 0; i < temp_b.size(); i++)
		{
			file << temp_b.at(i) << "\n";
		}
		
		//Write the edited map into file
		file << name << "\n";
		file << height << "\n";
		file << tile_to_win << "\n";
		for(int y = 0; y < height; y++)
		{
			file << string_map[y] << "\n";
		}
		
		//Write the temp_a vector into file
		for(int i = 0; i < temp_a.size()-1; i++)
		{
			file << temp_a.at(i) << "\n";
		}
		file.close();
	}
	temp_a.clear();
	temp_b.clear();
}

void Map_writer::Delete_map(std::string name, int height, int width)
{
	std::string line;
	std::fstream file;
	std::vector<std::string> temp_b, temp_a;//Temporary vectors for holding the file data that comes before and after the deleted map
	bool before_map = true;

	//Save the text file to temp_b and temp_a vectors
	file.open("Resources/map_file.txt", std::ios::in);
	if(file.is_open())
	{
		while(!file.eof())
		{
			std::getline (file,line);
			if(before_map == true)//Save the parts of file that come before the edited map into tem_b
			{
				if(line != name)//Copy till edited map
				{
					temp_b.push_back(line);
				}
				else//Advance read location over the edited file
				{
					std::getline (file,line);
					std::getline (file,line);
					for(int y = 0; y < height; y++)
					{
						std::getline (file,line);
					}
					before_map = false;
				}
			}
			else//Save the parts of file that come after the edited map into tem_a
			{
				temp_a.push_back(line);
			}
		}
		file.close();
	}

	file.open("Resources/map_file.txt", std::ios::out | std::ios::trunc);
	if(file.is_open())
	{
		//Write the temp_b vector into file
		for(int i = 0; i < temp_b.size()-1; i++)
		{
			file << temp_b.at(i) << "\n";
		}
		
		//Write the temp_a vector into file
		for(int i = 0; i < temp_a.size()-1; i++)
		{
			file << temp_a.at(i);
		}


		file.close();
	}
	temp_a.clear();
	temp_b.clear();
}