#include "Game.h"
#include "Base.h"
#include "Menu_handler.h"
#include "Map_reader.h"
#include "Edit_map.h"
#include "Audio_handler.h"

#include <SFML\Window\Event.hpp>
#include <sstream>

Game::Game(void)
{
	gamestate = MAIN_MENU;
	Map_reader map_reader;
	map_amount = map_reader.Read_Map_Names(map_names);
	Update();
}


Game::~Game(void)
{
}

void Game::Greate_window()//Sets the values of the main window
{
	main_window.create(sf::VideoMode(1000,800),"Ocean Maker",sf::Style::Default);
	main_window.setFramerateLimit(FRAMERATE);
}

void Game::Update()//Holds the main loop, gamestates and handles basic initialisation
{
	//Initialization (done here to avoid using the new call)
	Greate_window();
	sf::Clock game_time;
	
	Gameplay game_logic(sf::IntRect(0,0,1000,800), main_window);
	Draw_handler draw_handler(main_window);
	Camera camera(main_window);

	Menu_handler menu;
	//Audio_handler audio;
	int level_id = 0;

	//Editor variaples
	Edit_map editor(main_window);
	int width = 3, height = 3, mouse_wheel = 0;
	bool e_init_level = false, e_save = false;

	//Game loop
	while(main_window.isOpen())
	{
		sf::Event event;
		while (main_window.pollEvent(event))//Event handling
		{
			if (event.type == sf::Event::Closed)
			{
				main_window.close();
				gamestate = EXIT;
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				mouse_wheel = event.mouseWheel.delta;
			}
		}

		//Show main menu
		if (gamestate == MAIN_MENU)
		{
			menu.Main_menu(draw_handler,main_window,gamestate);
		}

		//Show level select menu
		else if (gamestate == SELECT_LEVEL)
		{
			menu.Select_map_menu(draw_handler,main_window,gamestate, map_amount);
			level_id = menu.getLevelId();
		}

		//Initialize level
		else if (gamestate == INIT_LEVEL)
		{
			game_logic.Initialize_level(map_names.at(level_id));
			gamestate = GAME;
		}

		//Gameplay
		else if (gamestate == GAME)
		{
			game_logic.Update(game_time.getElapsedTime(), draw_handler, gamestate);
			game_time.restart();//Notes! Must be right after gamelogic
		}

		//Actions upon completing a level
		else if (gamestate == LEVEL_CLEAR)
		{
			if(level_id < map_amount-1)//Change level if previous level wasn't the last
			{
				level_id++;
				gamestate = INIT_LEVEL;
			}
			else//Show victory screen if last level of the game is beaten
			{
				menu.Victory_Screen(draw_handler,gamestate);
			}
		}
		//Show game controls
		else if(gamestate == CONTROLS)
		{
			menu.Controls_menu(draw_handler,main_window,gamestate);
		}

		//Editor_______________________________________________________________________________________________
		//Select the greation of new level or editing existing level
		else if(gamestate == E_INIT_METHOD)
		{
			menu.Init_Editor_Menu(draw_handler,main_window,gamestate);
		}

		//Give width and height of a new map
		else if(gamestate == E_INIT_INPUT)
		{
			menu.Editor_Values_Menu(draw_handler,main_window,width,height,gamestate, e_init_level);
			if(e_init_level == true)
			{
				//Create map name from map the word "level" and map amount
				std::ostringstream conv;
				conv << map_amount+1;
				std::string temp = "level " + conv.str();

				editor.Initialize(temp,height,width);
				e_init_level = false;
				gamestate = E_EDITOR;
			}
		}

		//Load existing map for editing
		else if(gamestate == E_SELECT_LEVEL)
		{
			
			menu.Editor_Select_Menu(draw_handler,main_window,gamestate, map_amount,e_init_level);
			level_id = menu.getLevelId();
			if(e_init_level == true)
			{
				editor.Initialize(map_names.at(level_id));
				e_init_level = false;
				gamestate = E_EDITOR;
			}
		}

		//Delete selected map
		else if(gamestate == E_DELETE_LEVEL)
		{
			menu.Editor_Delete_Map_Menu(draw_handler,main_window,gamestate, map_names.at(level_id));
			if(menu.getConfirmDelete() == 2)
			{
				Map_writer writer;
				editor.Delete_map(map_names.at(level_id));
				menu.setConfirmDelete(0);
				map_names.erase(map_names.begin()+level_id);
				map_amount--;
				gamestate = E_SELECT_LEVEL;
			}
		}

		//Edit initialized map
		else if(gamestate == E_EDITOR)
		{
			editor.Update(draw_handler,gamestate,mouse_wheel,e_save);
			if(e_save == true)
			{
				map_amount++;
				map_names.push_back(editor.getName());
				e_save = false;
			}
		}
		//Editor_______________________________________________________________________________________________
		
		//Game exit
		else if(gamestate == EXIT)
		{
			main_window.close();
		}
		mouse_wheel = 0;
		draw_handler.Draw();//Draw everything into screen
	}

	main_window.close();//Close main window
}