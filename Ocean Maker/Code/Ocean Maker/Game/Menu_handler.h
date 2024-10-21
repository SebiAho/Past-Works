#pragma once
#include "Draw_handler.h"
#include "Input.h"
#include <SFML\Window\Window.hpp>
#include "Map_writer.h"

class Menu_handler
{
public:
	Menu_handler(void);
	~Menu_handler(void);

	void Main_menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate);
	void Select_map_menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate, int map_amount);//Allows player to select whis map he/she wants tp play
	void Controls_menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate);//Shows game controls to player
	void Victory_Screen(Draw_handler& _draw,int& _gamestate);//Screen thats shown upon clearing the last level
	
	//Editor Menus
	void Init_Editor_Menu(Draw_handler& _draw, sf::Window& _window, int &editorstate);//Select how to initialice level
	void Editor_Values_Menu(Draw_handler& _draw, sf::Window& _window, int& width, int& height, int &editorstate, bool& _init);//Allows player to select whis map he/she wants tp play
	void Editor_Select_Menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate, int map_amount, bool &_init);//Select map to edit
	void Editor_Delete_Map_Menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate, std::string map_name);//Select map to delete
	int getLevelId(){return level;};
	int getConfirmDelete(){return confirm_delete;};
	void setConfirmDelete(int value){confirm_delete = value;};
private:
	void Draw_background(Draw_handler& _draw);
	int level, controls_menu, confirm_delete;
};

