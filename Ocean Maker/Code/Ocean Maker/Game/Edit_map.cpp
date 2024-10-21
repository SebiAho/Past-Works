#include "Edit_map.h"
#include "Editor_Base_Values.h"

#include "Map_writer.h"
#include "Editor_map_reader.h"

#include "Input.h"
#include <iostream>

Edit_map::Edit_map(sf::RenderWindow& _window) : window(_window)
{
	camera = new Editor_camera(window);
}


Edit_map::~Edit_map(void)
{
	delete camera;
}

//_____________________________________________________________________________________________________________________
//Initialization for new level
void Edit_map::Initialize(std::string _name, int _height, int _width)
{
	name = _name;
	height = _height;
	width = _width;
	tile_values.Initialize();
	selected_object = selected_tile = tiles_to_win = 0;
	gridOn = TilesToChangeOn = change_all = true;

	viewPos = sf::Vector2f(300,200);

	//Initialize arrays
	for(int y = 0; y < height; y++)
	{
		string_map[y].resize(width);
		for(int x = 0; x < width; x++)
		{
			tiles[y][x] = 10;
			objects[y][x] = 0;
			int_map[y][x] = 5;
			string_map[y][x] = '#';
			tiles_to_change[y][x] = false;
		}
	}
	owerWrite = false;
}

//_____________________________________________________________________________________________________________________
//Initialization for existing level
void Edit_map::Initialize(std::string _name)
{
	name = _name;

	Editor_map_reader reader;
	reader.Read_map(name);

	height = reader.getHeight();
	width = reader.getWidth();

	tile_values.Initialize();
	selected_object = selected_tile = tiles_to_win = 0;
	gridOn = TilesToChangeOn = change_all = true;

	viewPos = sf::Vector2f(300,200);
	
	reader.Read_map(name);

	//Initialize arrays
	for(int y = 0; y < height; y++)
	{
		string_map[y] = reader.string_values[y];
		string_map[y].resize(width);
		for(int x = 0; x < width; x++)
		{
			tiles[y][x] = parser.Parse_from_file(string_map[y][x]).x;
			objects[y][x] = parser.Parse_from_file(string_map[y][x]).y;
			int_map[y][x] = parser.Parse_from_file(string_map[y][x]).z;
			tiles_to_change[y][x] = false;
		}
	}
	owerWrite = true;
}

void Edit_map::Delete_map(std::string _name)
{
	Editor_map_reader reader;
	reader.Read_map(_name);
	height = reader.getHeight();
	width = reader.getWidth();
	Map_writer writer;
	writer.Delete_map(_name,height,width);

}

//_____________________________________________________________________________________________________________________
//Upates the editor and draws the map
void Edit_map::Update(Draw_handler& _draw, int& editor_state, const int& _mouseWheel, bool& e_save)
{
	camera->Update(viewPos,sf::Vector2i(width*TILESIZE,height*TILESIZE));
	mouse_wheel = _mouseWheel;

	if(Input::Release_Key(sf::Keyboard::Escape))//Save map, close window and return to initialization console
	{
		if(owerWrite == false)
		{
			Save_new_map();
			e_save = true;
		}
		editor_state = E_INIT_METHOD;
		camera->setWiew(window.getDefaultView());
	}

	if(owerWrite == true && Input::Release_Key(sf::Keyboard::L))//Save and exit if editing existing map
	{
		Save_old_map();
		editor_state = E_INIT_METHOD;
		camera->setWiew(window.getDefaultView());
	}

	if(Input::Release_Key(sf::Keyboard::LAlt))//Return camera to starting location
	{
		viewPos.x = 300;
		viewPos.y = 200;
	}
	if(Input::Release_Key(sf::Keyboard::Space))//Switch grid On\Of
	{
		if(gridOn == false)
		{
			gridOn = true;
		}
		else
		{
			gridOn = false;
		}
	}
	if(Input::Release_Key(sf::Keyboard::RAlt))//Switch showing tile to change On\Of
	{
		if(TilesToChangeOn == false)
		{
			TilesToChangeOn = true;
		}
		else
		{
			TilesToChangeOn = false;
		}
	}
	if(Input::Release_Key(sf::Keyboard::M))//Set tiles to win max/min
	{
		if(change_all == true)
		{
			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					tiles_to_change[y][x] = true;
				}
			}
			tiles_to_win = height*width;
			change_all = false;
		}
		else
		{
			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					tiles_to_change[y][x] = false;
				}
			}
			tiles_to_win = 0;
			change_all = true;
		}
	}

	Tile_placement();//Call tile placement function

	//Move camera______________
	if(Input::Hold_Key(sf::Keyboard::W) || Input::Hold_Key(sf::Keyboard::Up))
	{
		viewPos.y -= 10;
	}
	if(Input::Hold_Key(sf::Keyboard::S) || Input::Hold_Key(sf::Keyboard::Down))
	{
		viewPos.y += 10;
	}
	if(Input::Hold_Key(sf::Keyboard::A) || Input::Hold_Key(sf::Keyboard::Left))
	{
		viewPos.x -= 10;
	}
	if(Input::Hold_Key(sf::Keyboard::D) || Input::Hold_Key(sf::Keyboard::Right))
	{
		viewPos.x += 10;
	}

	//Draw_____________________________________________________________________________________________________
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			_draw.Rectangle(sf::Vector2f((float)(x*TILESIZE),(float)(y*TILESIZE)),tile_values.getTile(tiles[y][x]).texture[1]);//Draw Tiles
			_draw.Rectangle(sf::Vector2f((float)(x*TILESIZE),(float)(y*TILESIZE)),tile_values.getTile(objects[y][x]).texture[1]);//Draw Objects
			
			if(gridOn == true)
			{
				_draw.Rectangle(sf::Vector2f((float)(x*TILESIZE),(float)(y*TILESIZE)),sf::Vector2f(100,0));//Draw grid
			}
			if(TilesToChangeOn == true && tiles_to_change[y][x] == true)
			{
				_draw.Rectangle(sf::Vector2f((float)(x*TILESIZE),(float)(y*TILESIZE)),sf::Vector2f(820,0));//Draw tiles to change
			}
		}
	}

	//Info text
	_draw.write(name,20,0,-120,sf::Color::Red);//Write map name
	_draw.write("Tiles to Change ",tiles_to_win,20,0,-80,sf::Color::Red);//Number tiles to win level
	if(owerWrite == false)
	{
		_draw.write("Press Esc to Save map and Exit editor ",20,0,-50,sf::Color::Red);//Save & Exit Instructions
	}
	else
	{
		_draw.write("Press Esc to Exit editor or L to Save map and Exit editor ",20,0,-50,sf::Color::Red);//Save & Exit Instructions
	}
	///Tile selection
	_draw.Rectangle(sf::Vector2f(camera->getWiew().getCenter().x-500,camera->getWiew().getCenter().y-400),sf::Vector2f(710,0),110,110);//Draw background to currently selected tile
	_draw.Rectangle(sf::Vector2f(camera->getWiew().getCenter().x-495,camera->getWiew().getCenter().y-395),tile_values.getTile(parser.Parse_to_map(selected_tile).x).texture[1]);//Draw currently seleceted tile
	_draw.Rectangle(sf::Vector2f(camera->getWiew().getCenter().x-495,camera->getWiew().getCenter().y-395),tile_values.getTile(parser.Parse_to_map(selected_tile).y).texture[1]);//Draw currently selected object

	//Tile explanation
	if(selected_tile == 1)//Write if transparent if said tile is selected 
	{
		_draw.write("Trans-\nparent",20,(int)camera->getWiew().getCenter().x-480,(int)camera->getWiew().getCenter().y-380,sf::Color::White);
	}
	else if(selected_tile == 2)//Write if transparent Solid if said tile is selected 
	{
		_draw.write("Trans-\nparent\nSolid",20,(int)camera->getWiew().getCenter().x-480,(int)camera->getWiew().getCenter().y-390,sf::Color::White);
	}
	else if(selected_tile == 0)//Write Player Start if said tile is selected 
	{
		_draw.write("Player\n Start",20,(int)camera->getWiew().getCenter().x-480,(int)camera->getWiew().getCenter().y-380,sf::Color::Red);
	}
}

//_____________________________________________________________________________________________________________________
//Contains code used in tile placement
void Edit_map::Tile_placement()
{
	//Convert map coordinates to mouse position
	mousePos.x = (int)(window.mapPixelToCoords(Input::Mouse_pos(window)).x/TILESIZE);
	mousePos.y = (int)(window.mapPixelToCoords(Input::Mouse_pos(window)).y/TILESIZE);

	//Code for placing tiles on mouse position
	if(mousePos.x > -1 && mousePos.x < width && mousePos.y > -1 && mousePos.y < height)//Check if mouse cursor is inside the map borders
	{
		if(Input::Hold_mouse(sf::Mouse::Left))//Place selected tile
		{
			tiles[mousePos.y][mousePos.x] = parser.Parse_to_map(selected_tile).x;
			objects[mousePos.y][mousePos.x] = parser.Parse_to_map(selected_tile).y;
			int_map[mousePos.y][mousePos.x] = parser.Parse_to_map(selected_tile).z;
		}
		else if(Input::Hold_mouse(sf::Mouse::Right))//Place default tile
		{
			tiles[mousePos.y][mousePos.x] = 10;
			objects[mousePos.y][mousePos.x] = 0;
			int_map[mousePos.y][mousePos.x] = 5;
		}
	}

	//Change selected tile
	if(mouse_wheel < 0 && selected_tile - 1 > -1)
	{
		selected_tile--;
	}
	else if(mouse_wheel > 0 && selected_tile < 23)
	{
		selected_tile++;
	}

	//Add 1 to the tiles_to_win 
	if(Input::Hold_Key(sf::Keyboard::Q) || Input::Hold_mouse(sf::Mouse::Middle))
	{
		if(tiles_to_change[mousePos.y][mousePos.x] == false)
		{
			tiles_to_change[mousePos.y][mousePos.x] = true;
			tiles_to_win++;
		}
	}
	//Remove 1 to the tiles_to_win 
	if(Input::Hold_Key(sf::Keyboard::E) || Input::Hold_mouse(sf::Mouse::XButton1))
	{
		if(tiles_to_change[mousePos.y][mousePos.x] == true)
		{
			tiles_to_change[mousePos.y][mousePos.x] = false;
			tiles_to_win--;
		}
	}
}

//_____________________________________________________________________________________________________________________
//Saves the map onto file
void Edit_map::Save_new_map()
{
	parser.Parse_to_string(height,width,string_map,int_map);
	Map_writer map_writer;
	map_writer.Write_map(string_map,name,tiles_to_win,height, width);
}

void Edit_map::Save_old_map()
{
	parser.Parse_to_string(height,width,string_map,int_map);
	Map_writer map_writer;
	map_writer.Overwrite_map(string_map,name,tiles_to_win,height,width);
}