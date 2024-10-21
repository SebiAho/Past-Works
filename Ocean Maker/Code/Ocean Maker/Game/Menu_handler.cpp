#include "Menu_handler.h"
#include "Base.h"

#include <SFML\System.hpp>
#include <SFML\Graphics\Rect.hpp>

#include <iostream>

Menu_handler::Menu_handler(void):level(0),controls_menu(0), confirm_delete(0)
{

}


Menu_handler::~Menu_handler(void)
{
}

void Menu_handler::Main_menu(Draw_handler& _draw, sf::Window& _window, int& _gamestate)
{
	//Init button location rectangles
	sf::Rect<int> Start(SCREEN_WIDTH/2-100,100,200,75);
	sf::Rect<int> Editor(Start.left,Start.top+125,200,75);
	sf::Rect<int> Controls(Start.left,Editor.top+125,200,75);
	sf::Rect<int> Exit(Start.left,Controls.top+125,200,75);

	//Update________________________________________________________

	//Start game
	if(Start.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))
	{
		_gamestate = SELECT_LEVEL;
	}

	//Editor
	if(Editor.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))
	{
		_gamestate = E_INIT_METHOD;
	}

	//Show controls
	if(Controls.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))
	{
		_gamestate = CONTROLS;
	}

	//Exit game
	if(Input::Release_mouse(sf::Mouse::Left) && Exit.contains(Input::Mouse_pos(_window)))
	{
		_gamestate = EXIT;
	}

	//Draw code______________________________________________________

	Draw_background(_draw);//Draw background
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Write Game Title
	
	//Draw buttons
	_draw.Rectangle(sf::Vector2f((float)Start.left,(float)Start.top),sf::Vector2f(500,100),Start.width,Start.height);//Draw Start button background
	_draw.write("Start Game",35,Start.left+8,Start.top+12,sf::Color::White);//Write button text outline
	_draw.write("Start Game",35,Start.left+8,Start.top+10,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Editor.left,(float)Editor.top),sf::Vector2f(500,100),Controls.width,Controls.height);//Draw Controls button background
	_draw.write("Editor",35,Editor.left+55,Editor.top+12,sf::Color::White);//Write button text outline
	_draw.write("Editor",35,Editor.left+55,Editor.top+10,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Controls.left,(float)Controls.top),sf::Vector2f(500,100),Controls.width,Controls.height);//Draw Controls button background
	_draw.write("Controls",35,Controls.left+30,Controls.top+12,sf::Color::White);//Write button text outline
	_draw.write("Controls",35,Controls.left+30,Controls.top+10,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Exit.left,(float)Exit.top),sf::Vector2f(500,100),Exit.width,Exit.height);//Draw Exit button background
	_draw.write("Exit",35,Exit.left+70,Exit.top+12,sf::Color::White);//Write button text outline
	_draw.write("Exit",35,Exit.left+70,Exit.top+10,sf::Color::Red);//Write button text
}

void Menu_handler::Select_map_menu(Draw_handler& _draw, sf::Window& _window, int& _gamestate, int map_amount)//Allows player to select whis map he/she wants tp play
{
	//Init button location rectangles
	sf::Rect<int> Left(SCREEN_WIDTH/2-115,100,80,75);
	sf::Rect<int> Right(Left.left+150,Left.top,80,75);
	sf::Rect<int> Select(Left.left+65,Left.top+75,103,50);
	sf::Rect<int> Return(Select.left,Select.top + 100,100,50);

	//Update________________________________________________________
	if(Left.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Previous level
	{
		if(level >= 1)
		{
			level--;
		}
	}

	if(Right.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))//Next level
	{
		if(level < map_amount-1)
		{
			level++;
		}
	}

	if(Select.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Start selected level
	{
		_gamestate = INIT_LEVEL;
	}

	if(Return.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Return to main menu
	{
		_gamestate = MAIN_MENU;
	}


	//Draw code______________________________________________________
	Draw_background(_draw);
	
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Game Title

	_draw.write("Select level",30,SCREEN_WIDTH/2-90,61,sf::Color::White);//Menu title outline
	_draw.write("Select level",30,SCREEN_WIDTH/2-90,60,sf::Color::Red);//Menu title

	_draw.write("",level+1,35,(float)(Left.left+85),(float)(Left.top+10));//Level numper

	//Arrow buttons
	_draw.Rectangle(sf::Vector2f((float)Left.left,(float)Left.top),sf::Vector2f(400,0),Left.width,Left.height);//Draw Left arrow button background
	_draw.write("-",50,Left.left-25,Left.top+1,sf::Color::White);//Write button text outline
	_draw.write("-",50,Left.left-25,Left.top,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Right.left,(float)Right.top),sf::Vector2f(500,0),Right.width,Right.height);//Draw Right arrow button background
	_draw.write("+",50,Right.left+80,Right.top+1,sf::Color::White);//Write button text outline
	_draw.write("+",50,Right.left+80,Right.top,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Select.left,(float)Select.top),sf::Vector2f(600,0),Select.width,Select.height);//Draw Select arrow button background
	_draw.write("Select",30,Select.left+5,Select.top+51,sf::Color::White);//Write button text outline
	_draw.write("Select",30,Select.left+5,Select.top+50,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Return.left,(float)Return.top),sf::Vector2f(400,100),Return.width,Return.height);//Draw Return to main menu button background
	_draw.write("Return",30,Return.left+5,Return.top+1,sf::Color::White);//Write button text outline
	_draw.write("Return",30,Return.left+5,Return.top,sf::Color::Red);//Write button text
}

void Menu_handler::Victory_Screen(Draw_handler& _draw,int& _gamestate)//Screen thats shown upon clearing the last level
{
	if(Input::Release_Key(sf::Keyboard::Space))
	{
		_gamestate = MAIN_MENU;
	}
	_draw.write("Congratulations!",40,SCREEN_WIDTH/2-7*20-10,SCREEN_HEIGHT/2-200,sf::Color::Yellow);
	_draw.write("You have beaten the last map!",40,SCREEN_WIDTH/2-14*20,SCREEN_HEIGHT/2-100,sf::Color::Yellow);
	_draw.write("Press Space to Return to the Main Menu",30,SCREEN_WIDTH/2-19*15,SCREEN_HEIGHT/2,sf::Color::Yellow);

	Draw_background(_draw);
}

void Menu_handler::Controls_menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate)//Shows game controls to player
{
	sf::Vector2i pos(300,120);
	sf::Rect<int> Return(SCREEN_WIDTH/2-50,600,100,50);

	if(Return.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Return to main menu
	{
		_gamestate = MAIN_MENU;
	}

	Draw_background(_draw);

	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Write Game Title

	if(controls_menu == 0)//Show Game controls
	{
		sf::Rect<int> Switch(SCREEN_WIDTH-365,520,80,75);

		if(Switch.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))
		{
			controls_menu = 1;
		}
		_draw.write("Game Controls:",35,pos.x,75,sf::Color::White);
		_draw.write("Key:\nW & Up\nS & Down\nA & Left\nD & Right\nSpace\nEnter\nEsc",30,pos.x,pos.y,sf::Color::White);
		_draw.write("Function:\nMove Up\nMove Down\nMove Left\nMove Right\nToggle Grid On/Off\nRestart Level\nReturn to Level Select",30,pos.x+200,pos.y,sf::Color::White);

		//Draw Button for switching between control menus
		_draw.Rectangle(sf::Vector2f((float)Switch.left,(float)Switch.top),sf::Vector2f(500,0),Switch.width,Switch.height);
		_draw.write("Editor Controls:",30,Switch.left-240,Switch.top+12,sf::Color::White);
		_draw.write("Editor Controls:",30,Switch.left-240,Switch.top+11,sf::Color::Red);
	}
	else//Show Editor controls
	{
		sf::Rect<int> Switch(290,520,80,75);

		if(Switch.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))
		{
			controls_menu = 0;
		}

		_draw.write("Editor Controls:",35,pos.x-150,75,sf::Color::White);
		_draw.write("Key:\nLeft Mouse\nRight Mouse\nWASD & Arrow\nLeft Alt\nSpace\nMouse Wheel\nMiddle Mouse & Q\nMouse Side & E\nRight Alt\nM",30,pos.x-150,pos.y,sf::Color::White);
		_draw.write("Function:\nPlace tile on map\nRemove tile from map\nControl camera\nMove camera to start pos\nToggle grid\nChange Selected Tile\nAdd tile to be changed\nRemove tile to be changed\nToggle tiles to change\nSet tiles to change Max/Min",30,pos.x+160,pos.y,sf::Color::White);

		//Draw Button for switching between control menus
		_draw.Rectangle(sf::Vector2f((float)Switch.left,(float)Switch.top),sf::Vector2f(400,0),Switch.width,Switch.height);
		_draw.write("Game Controls:",30,Switch.left+100,Switch.top+12,sf::Color::White);
		_draw.write("Game Controls:",30,Switch.left+100,Switch.top+11,sf::Color::Red);
	}

	_draw.Rectangle(sf::Vector2f((float)Return.left,(float)Return.top),sf::Vector2f(400,100),Return.width,Return.height);//Draw Return to main menu button background
	_draw.write("Return",30,Return.left+5,Return.top+1,sf::Color::White);//Write button text outline
	_draw.write("Return",30,Return.left+5,Return.top,sf::Color::Red);//Write button text
	
}

//Editor Menus_________________________________________________________________________________________________________________
void Menu_handler::Init_Editor_Menu(Draw_handler& _draw, sf::Window& _window, int &editorstate)//Select how to initialise level
{
	//Init button location rectangles
	sf::Rect<int> Start(SCREEN_WIDTH/2-100,100,200,75);
	sf::Rect<int> Controls(Start.left,Start.top+125,200,75);
	sf::Rect<int> Return(Start.left,Controls.top+125,200,75);

	//Update________________________________________________________
	if(Start.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))//Give map values
	{
		editorstate = E_INIT_INPUT;
	}
	if(Controls.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Select level
	{
		editorstate = E_SELECT_LEVEL;
	}
	if(Input::Release_mouse(sf::Mouse::Left) && Return.contains(Input::Mouse_pos(_window)))//Return to main menu
	{
		editorstate = MAIN_MENU;
	}

	//Draw code______________________________________________________

	Draw_background(_draw);//Draw background
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Write Game Title
	
	//Draw buttons
	_draw.Rectangle(sf::Vector2f((float)Start.left,(float)Start.top),sf::Vector2f(500,100),Start.width,Start.height);//Draw button background
	_draw.write("Create New Map",24,Start.left+9,Start.top+19,sf::Color::White);//Write button text outline
	_draw.write("Create New Map",24,Start.left+9,Start.top+17,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Controls.left,(float)Controls.top),sf::Vector2f(500,100),Controls.width,Controls.height);//Draw button background
	_draw.write("Edit Existing Map",24,Controls.left+8,Controls.top+20,sf::Color::White);//Write button text outline
	_draw.write("Edit Existing Map",24,Controls.left+8,Controls.top+18,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Return.left,(float)Return.top),sf::Vector2f(500,100),Return.width,Return.height);//Draw button background
	_draw.write("Return",30,Return.left+55,Return.top+14,sf::Color::White);//Write button text outline
	_draw.write("Return",30,Return.left+55,Return.top+12,sf::Color::Red);//Write button text
}

void Menu_handler::Editor_Values_Menu(Draw_handler& _draw, sf::Window& _window, int& width, int& height, int &editorstate, bool& _init)//Allows player to select whis map he/she wants tp play
{
	//Init button location rectangles
	sf::Rect<int> Left(SCREEN_WIDTH/2-115,100,80,75);
	sf::Rect<int> Right(Left.left+150,Left.top,80,75);

	sf::Rect<int> R_Left(SCREEN_WIDTH/2-115,Right.top+120,80,75);
	sf::Rect<int> R_Right(Left.left+150,R_Left.top,80,75);

	sf::Rect<int> Select(R_Left.left+65,R_Left.top+75,103,50);

	sf::Rect<int> Return(Select.left,Select.top+100,100,50);

	//Update_________________________________________________________________________________________
	//Enter map name


	//Decrease width value
	if(Left.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))
	{
		if(width > 3)
		{
			width--;
		}
	}

	//Increase width value
	if(Right.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))
	{
		if(width < 20)
		{
			width++;
		}
	}

	//Decrease height value
	if(R_Left.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Previous level
	{
		if(height > 3)
		{
			height--;
		}
	}

	//Increase height value
	if(R_Right.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))//Next level
	{
		if(height < 20)
		{
			height++;
		}
	}

	if(Select.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Start selected level
	{
		_init = true;;
	}

	if(Return.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Return to main menu
	{
		editorstate = E_INIT_METHOD;
	}


	//Draw code______________________________________________________
	Draw_background(_draw);
	
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Game Title

	//Width selection____________________________________________
	_draw.write("Select width",30,SCREEN_WIDTH/2-90,Left.top - 40,sf::Color::White);//Menu title outline
	_draw.write("",width,35,(float)(Left.left+85),(float)(Left.top+10));//Level numper

	//Lower width value
	_draw.Rectangle(sf::Vector2f((float)Left.left,(float)Left.top),sf::Vector2f(400,0),Left.width,Left.height);//Draw Left arrow button background
	_draw.write("-",50,Left.left-25,Left.top+1,sf::Color::White);//Write button text outline

	//Increase width value
	_draw.Rectangle(sf::Vector2f((float)Right.left,(float)Right.top),sf::Vector2f(500,0),Right.width,Right.height);//Draw Right arrow button background
	_draw.write("+",50,Right.left+80,Right.top+1,sf::Color::White);//Write button text outline

	//Height selection____________________________________________
	_draw.write("Select height",30,SCREEN_WIDTH/2-90,R_Left.top - 40,sf::Color::White);//Menu title outline
	_draw.write("",height,35,(float)(R_Left.left+85),(float)(R_Left.top+10));//Level numper

	//Lower width value
	_draw.Rectangle(sf::Vector2f((float)R_Left.left,(float)R_Left.top),sf::Vector2f(400,0),Left.width,Left.height);//Draw Left arrow button background
	_draw.write("-",50,R_Left.left-25,R_Left.top+1,sf::Color::White);//Write button text outline

	//Increase width value
	_draw.Rectangle(sf::Vector2f((float)R_Right.left,(float)R_Right.top),sf::Vector2f(500,0),Right.width,Right.height);//Draw Right arrow button background
	_draw.write("+",50,R_Right.left+80,R_Right.top+1,sf::Color::White);//Write button text outline

	//Other buttons______________________________________________
	//Select values button
	_draw.Rectangle(sf::Vector2f((float)Select.left,(float)Select.top),sf::Vector2f(600,0),Select.width,Select.height);//Draw Select arrow button background
	_draw.write("Select",30,Select.left+5,Select.top+51,sf::Color::White);//Write button text outline


	//Return to Main menu
	_draw.Rectangle(sf::Vector2f((float)Return.left,(float)Return.top),sf::Vector2f(400,100),Return.width,Return.height);//Draw Return to main menu button background
	_draw.write("Return",30,Return.left+5,Return.top+1,sf::Color::White);//Write button text outline
	_draw.write("Return",30,Return.left+5,Return.top,sf::Color::Red);//Write button text
}

void Menu_handler::Editor_Select_Menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate, int map_amount, bool &_init)//Select map to edit
{
	//Init button location rectangles
	sf::Rect<int> Left(SCREEN_WIDTH/2-115,100,80,75);
	sf::Rect<int> Right(Left.left+150,Left.top,80,75);
	sf::Rect<int> Select(Left.left+65,Left.top+75,103,50);
	sf::Rect<int> Return(Select.left,Select.top + 200,100,50);
	sf::Rect<int> Delete(Return.left + 300,Return.top + 250,100,50);

	//Update________________________________________________________
	if(Left.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Previous level
	{
		if(level >= 1)
		{
			level--;
		}
	}

	if(Right.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))//Next level
	{
		if(level < map_amount-1)
		{
			level++;
		}
	}

	if(Select.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Start selected level
	{
		_init = true;
	}

	if(Return.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Return to main menu
	{
		_gamestate = E_INIT_METHOD;
	}
	
	if(Delete.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Return to main menu
	{
		confirm_delete = 0;
		_gamestate = E_DELETE_LEVEL;
	}
	confirm_delete = 0;

	//Draw code______________________________________________________
	Draw_background(_draw);
	
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Game Title

	_draw.write("Select level",30,SCREEN_WIDTH/2-90,61,sf::Color::White);//Menu title outline
	_draw.write("Select level",30,SCREEN_WIDTH/2-90,60,sf::Color::Red);//Menu title

	_draw.write("",level+1,35,(float)(Left.left+85),(float)(Left.top+10));//Level numper

	//Arrow buttons
	_draw.Rectangle(sf::Vector2f((float)Left.left,(float)Left.top),sf::Vector2f(400,0),Left.width,Left.height);//Draw Left arrow button background
	_draw.write("-",50,Left.left-25,Left.top+1,sf::Color::White);//Write button text outline
	_draw.write("-",50,Left.left-25,Left.top,sf::Color::Red);//Write button text

	_draw.Rectangle(sf::Vector2f((float)Right.left,(float)Right.top),sf::Vector2f(500,0),Right.width,Right.height);//Draw Right arrow button background
	_draw.write("+",50,Right.left+80,Right.top+1,sf::Color::White);//Write button text outline
	_draw.write("+",50,Right.left+80,Right.top,sf::Color::Red);//Write button text

	//Select button
	_draw.Rectangle(sf::Vector2f((float)Select.left,(float)Select.top),sf::Vector2f(600,0),Select.width,Select.height);//Draw Select arrow button background
	_draw.write("Select",30,Select.left+5,Select.top+51,sf::Color::White);//Write button text outline
	_draw.write("Select",30,Select.left+5,Select.top+50,sf::Color::Red);//Write button text

	//Return button
	_draw.Rectangle(sf::Vector2f((float)Return.left,(float)Return.top),sf::Vector2f(400,100),Return.width,Return.height);//Draw Return to main menu button background
	_draw.write("Return",30,Return.left+5,Return.top+1,sf::Color::White);//Write button text outline
	_draw.write("Return",30,Return.left+5,Return.top,sf::Color::Red);//Write button text

	//Delete button
	_draw.Rectangle(sf::Vector2f((float)Delete.left,(float)Delete.top),sf::Vector2f(400,100),Delete.width,Delete.height);//Draw Delete to main menu button background
	_draw.write("Delete",30,Delete.left+5,Delete.top+1,sf::Color::White);//Write button text outline
	_draw.write("Delete",30,Delete.left+5,Delete.top,sf::Color::Red);//Write button text
}

void Menu_handler::Editor_Delete_Map_Menu(Draw_handler& _draw,sf::Window& _window, int& _gamestate, std::string map_name)//Select map to delete
{
	//Init button location rectangles
	sf::Rect<int> No(SCREEN_WIDTH/2-115,160,80,75);
	sf::Rect<int> Yes(No.left+150,No.top,80,75);

	//Update________________________________________________________
	if(No.contains(Input::Mouse_pos(_window))&&Input::Release_mouse(sf::Mouse::Left))//Previous level
	{
		_gamestate = E_SELECT_LEVEL;
	}

	if(Yes.contains(Input::Mouse_pos(_window)) && Input::Release_mouse(sf::Mouse::Left))//Next level
	{
		confirm_delete++;
	}
	
	//Draw code______________________________________________________
	Draw_background(_draw);
	
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,12,sf::Color::White);//Write Game Title outline
	_draw.write("OCEAN MAKER",45,SCREEN_WIDTH/2-140,10,sf::Color::Blue);//Game Title

	_draw.write("Delete level\n" + map_name+ "\nAre you sure?",30,SCREEN_WIDTH/2-90,61,sf::Color::White);//Ask convirmation message


	//Arrow buttons
	_draw.Rectangle(sf::Vector2f((float)No.left,(float)No.top),sf::Vector2f(400,0),No.width,No.height);//Draw Left arrow button background
	_draw.write("No",30,No.left-40,No.top+10,sf::Color::White);//Write button text outline

	_draw.Rectangle(sf::Vector2f((float)Yes.left,(float)Yes.top),sf::Vector2f(500,0),Yes.width,Yes.height);//Draw Right arrow button background
	_draw.write("Yes",30,Yes.left+80,Yes.top+10,sf::Color::White);//Write button text outline

	if(confirm_delete == 2)
	{
		level--;
	}
}

//_______________________________________________________________________________________________________
void Menu_handler::Draw_background(Draw_handler& _draw)
{
	//Draw Menu Background
	for(int y = 0; y < T_INSCREEN_Y; y++)
	{
		for(int x = 0; x < T_INSCREEN_X; x++)
		{
			if(x == 0 || x == T_INSCREEN_X-1 || y == T_INSCREEN_Y-1)
			{
				_draw.Rectangle(sf::Vector2f((float)x*TILESIZE,(float)y*TILESIZE),sf::Vector2f(100,200));//Draw water tiles
			}
			else
			{
				_draw.Rectangle(sf::Vector2f((float)x*TILESIZE,(float)y*TILESIZE),sf::Vector2f(100,100));//Draw stone tiles
			}
		}
	}
}