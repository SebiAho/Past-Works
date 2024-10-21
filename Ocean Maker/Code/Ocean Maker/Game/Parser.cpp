#include "Parser.h"

Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}

sf::Vector3i Parser::Parse_to_map(int tile_type)
{
	sf::Vector3i t_value;

	if(tile_type == 0)//Player starting location
	{
		t_value.x = 17;
		t_value.y = 0;
		t_value.z = 0;
	}

	else if(tile_type == 1)//Transparent
	{
		t_value.x = 0;
		t_value.y = 0;
		t_value.z = 1;
	}

	else if(tile_type == 2)//Transparent (solid)
	{
		t_value.x = 0;
		t_value.y = 1;
		t_value.z = 2;
	}

	else if(tile_type == 3)//Grass
	{
		t_value.x = 2;
		t_value.y = 0;
		t_value.z = 3;
	}

	else if(tile_type == 4)//Stone floor
	{
		t_value.x = 3;
		t_value.y = 0;
		t_value.z = 4;
	}

	else if(tile_type == 5)//Dirt
	{
		t_value.x = 10;
		t_value.y = 0;
		t_value.z = 5;
	}

	else if(tile_type == 6)//Sand
	{
		t_value.x = 16;
		t_value.y = 0;
		t_value.z = 6;
	}

	else if(tile_type == 7)//Rock Grass
	{
		t_value.x = 2;
		t_value.y = 11;
		t_value.z = 7;
	}
		
	else if(tile_type == 8)//Rock Stone
	{
		t_value.x = 3;
		t_value.y = 11;
		t_value.z = 8;
	}

	else if(tile_type == 9)//Rock Dirt
	{
		t_value.x = 10;
		t_value.y = 11;
		t_value.z = 9;
	}
	
	else if(tile_type == 10)//Rock Sand
	{
		t_value.x = 16;
		t_value.y = 11;
		t_value.z = 10;
	}

	else if(tile_type == 11)//Pyramid Grass
	{
		t_value.x = 2;
		t_value.y = 8;
		t_value.z = 11;
	}
	
	else if(tile_type == 12)//Pyramid Stone
	{
		t_value.x = 3;
		t_value.y = 8;
		t_value.z = 12;
	}

	else if(tile_type == 13)//Pyramid Dirt
	{
		t_value.x = 10;
		t_value.y = 8;
		t_value.z = 13;
	}

	else if(tile_type == 14)//Pyramid Sand
	{
		t_value.x = 16;
		t_value.y = 8;
		t_value.z = 14;
	}

	else if(tile_type == 15)//Wall front
	{
		t_value.x = 0;
		t_value.y= 14;
		t_value.z = 15;
	}

	else if(tile_type == 16)//Wall Top
	{
		t_value.x = 0;
		t_value.y = 15;
		t_value.z = 16;
	}

	else if(tile_type == 17)//Water
	{
		t_value.x = 4;
		t_value.y = 0;
		t_value.z = 17;
	}

	else if(tile_type == 18)//Lava
	{
		t_value.x = 5;
		t_value.y = 0;
		t_value.z = 18;
	}

	else if(tile_type == 19)//Ice
	{
		t_value.x = 6;
		t_value.y = 0;
		t_value.z = 19;
	}

	else if(tile_type == 20)//Red Ice
	{
		t_value.x = 7;
		t_value.y = 0;
		t_value.z = 20;
	}
	
	else if(tile_type == 21)//Mirror ice
	{
		t_value.x= 9;
		t_value.y = 0;
		t_value.z = 21;
	}

	else if(tile_type == 22)//Ghost Transparent
	{
		t_value.x = 12;
		t_value.y = 0;
		t_value.z = 22;
	}

	else if(tile_type == 23)//Ghost
	{
		t_value.x = 12;
		t_value.y = 13;
		t_value.z = 23;
	}



	return t_value;
}

void Parser::Parse_to_string(int height, int width, std::string string_map[MAX_MAP_HEIGTH], int int_map[MAX_MAP_HEIGTH][MAX_MAP_HEIGTH])
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(int_map[y][x] == 0)//Player starting location
			{
				string_map[y][x] = 'P';
			}

			if(int_map[y][x] == 1)//Transparent
			{
				string_map[y][x] = '0';
			}
			else if(int_map[y][x] == 2)//Transparent (solid)
			{
				string_map[y][x] = '#';
			}


			else if(int_map[y][x] == 3)//Grass
			{
				string_map[y][x] = '.';
			}
			else if(int_map[y][x] == 4)//Stone floor
			{
				string_map[y][x] = '-';
			}
			else if(int_map[y][x] == 5)//Dirt
			{
				string_map[y][x] = ',';
			}
			else if(int_map[y][x] == 6)//Sand
			{
				string_map[y][x] = 's';
			}


			else if(int_map[y][x] == 7)//Rock Grass
			{
				string_map[y][x] = '1';
			}
			else if(int_map[y][x] == 8)//Rock Stone
			{
				string_map[y][x] = '2';
			}
			else if(int_map[y][x] == 9)//Rock Dirt
			{
				string_map[y][x] = '3';
			}
			else if(int_map[y][x] == 10)//Rock Sand
			{
				string_map[y][x] = '4';
			}
	
			
			else if(int_map[y][x] == 11)//Pyramid Grass
			{
				string_map[y][x] = '5';
			}
				else if(int_map[y][x] == 12)//Pyramid Stone
			{
				string_map[y][x] = '6';
			}
			else if(int_map[y][x] == 13)//Pyramid Dirt
			{
				string_map[y][x] = '7';
			}
					else if(int_map[y][x] == 14)//Pyramid Sand
			{
				string_map[y][x] = '8';
			}


			else if(int_map[y][x] == 15)//Wall front
			{
				string_map[y][x] = 'F';
			}
			else if(int_map[y][x] == 16)//Wall Top
			{
				string_map[y][x] = 'f';
			}

			else if(int_map[y][x] == 17)//Water
			{
				string_map[y][x] = 'w';
			}

			else if(int_map[y][x] == 18)//Lava
			{
				string_map[y][x] = 'L';
			}

			else if(int_map[y][x] == 19)//Ice
			{
				string_map[y][x] = 'I';
			}

			else if(int_map[y][x] == 20)//Red Ice
			{
				string_map[y][x] = 'i';
			}

			else if(int_map[y][x] == 21)//Mirror ice
			{
				string_map[y][x] = 'M';
			}
			
			else if(int_map[y][x] == 22)//Ghost Transparent
			{
				string_map[y][x] = 'g';
			}

			else if(int_map[y][x] == 23)//Ghost
			{
				string_map[y][x] = 'G';
			}
	
		}
	}
}

sf::Vector3i Parser::Parse_from_file(char char_value)
{
	sf::Vector3i t_value;

	if(char_value == 'P')//Player starting location
	{
		t_value.x = 17;
		t_value.y = 0;
		t_value.z = 0;
	}

	else if(char_value == '0')//Transparent
	{
		t_value.x = 0;
		t_value.y = 0;
		t_value.z = 1;
	}

	else if(char_value == '#')//Transparent (solid)
	{
		t_value.x = 0;
		t_value.y = 1;
		t_value.z = 2;
	}


	else if(char_value == '.')//Grass
	{
		t_value.x = 2;
		t_value.y = 0;
		t_value.z = 3;
	}

	else if(char_value == '-')//Stone floor
	{
		t_value.x = 3;
		t_value.y = 0;
		t_value.z = 4;
	}

	else if(char_value == ',')//Dirt
	{
		t_value.x = 10;
		t_value.y = 0;
		t_value.z = 5;
	}
	
	else if(char_value == 's')//Sand
	{
		t_value.x = 16;
		t_value.y = 0;
		t_value.z = 6;
	}


	else if(char_value == '1')//Rock Grass
	{
		t_value.x = 2;
		t_value.y = 11;
		t_value.z = 7;
	}

	else if(char_value == '2')//Rock Stone
	{
		t_value.x = 3;
		t_value.y = 11;
		t_value.z = 8;
	}

	else if(char_value == '3')//Rock Dirt
	{
		t_value.x = 10;
		t_value.y = 11;
		t_value.z = 9;
	}

	else if(char_value == '4')//Rock Sand
	{
		t_value.x = 16;
		t_value.y = 11;
		t_value.z = 10;
	}


	else if(char_value == '5')//Pyramid Grass
	{
		t_value.x = 2;
		t_value.y = 8;
		t_value.z = 11;
	}

	else if(char_value == '6')//Pyramid Stone
	{
		t_value.x = 3;
		t_value.y = 8;
		t_value.z = 12;
	}

	else if(char_value == '7')//Pyramid Dirt
	{
		t_value.x = 10;
		t_value.y = 8;
		t_value.z = 13;
	}

	else if(char_value == '8')//Pyramid Sand
	{
		t_value.x = 16;
		t_value.y = 8;
		t_value.z = 14;
	}


	else if(char_value == 'F')//Wall front
	{
		t_value.x = 0;
		t_value.y= 14;
		t_value.z = 15;
	}

	else if(char_value == 'f')//Wall Top
	{
		t_value.x = 0;
		t_value.y = 15;
		t_value.z = 16;
	}

	else if(char_value == 'w')//Water
	{
		t_value.x = 4;
		t_value.y = 0;
		t_value.z = 17;
	}

	else if(char_value == 'L')//Lava
	{
		t_value.x = 5;
		t_value.y = 0;
		t_value.z = 18;
	}

	else if(char_value == 'I')//Ice
	{
		t_value.x = 6;
		t_value.y = 0;
		t_value.z = 19;
	}

	else if(char_value == 'i')//Red Ice
	{
		t_value.x = 7;
		t_value.y = 0;
		t_value.z = 20;
	}
	
	else if(char_value == 'M')//Mirror ice
	{
		t_value.x= 9;
		t_value.y = 0;
		t_value.z = 21;
	}

	else if(char_value == 'g')//Grave
	{
		t_value.x = 12;
		t_value.y = 0;
		t_value.z = 22;
	}

	else if(char_value == 'G')//Ghost
	{
		t_value.x = 12;
		t_value.y = 13;
		t_value.z = 23;
	}
	return t_value;
}