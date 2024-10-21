#include "Gameplay.h"
#include "Base.h"
#include "Input.h"

#include <iostream>
Gameplay::Gameplay(sf::IntRect _bounds,  sf::RenderWindow& _window) : bounds(_bounds), window(_window)
{

	camera = new Camera(_window);
	audio.Load_sound_files();
}


Gameplay::~Gameplay(void)
{
	delete camera;
}

void Gameplay::Update(const sf::Time& _time, Draw_handler& _draw, int& _gamestate)//Handles any changes to level/player done after initialization
{
	time = _time;

	

//Update code________________________________________________________________________

	player.Update(_time, map);

	camera->Update(player.getTextPosF(), map.getMapSize());
	//Player collision check
	//Up
	if(map.Is_Solid(player.getPos(),-TILESIZE,0))
	{
		player.setSpeed(UP,0);
	}
	//Down
	if(map.Is_Solid(player.getPos(),(float)TILESIZE,0))
	{
		player.setSpeed(DOWN,0);
	}
	//Left
	if(map.Is_Solid(player.getPos(),0,-TILESIZE))
	{
		player.setSpeed(LEFT,0);
	}
	//Right
	if(map.Is_Solid(player.getPos(),0,(float)TILESIZE))
	{
		player.setSpeed(RIGHT,0);
	}

	//Update tiles___________________________________________________________________
	Tile_Update(player,map);

	//Other funktions_______________________________________
	//See if level has been completed
	if(tiles_changed == map.getTilesToWin())
	{
		level_clear = true;
	}

	//Restart level
	if(Input::Press_Key(sf::Keyboard::Return))
	{
		_gamestate = INIT_LEVEL;
	}

	//Return to Level select
	if(Input::Release_Key(sf::Keyboard::Escape))
	{
		_gamestate = SELECT_LEVEL;
		camera->setWiew(window.getDefaultView());
	}

//Draw code__________________________________________________________________________
	map.Draw(_draw, _time.asSeconds());
	player.Hud(_draw,camera->getWiew().getCenter());
	player.Draw(_draw);
	Hud(_draw);
	if(level_clear == true)
	{
		if(Input::Release_Key(sf::Keyboard::Space))
		{
			camera->setWiew(window.getDefaultView());
			_gamestate = LEVEL_CLEAR;
		}
		Level_clear_menu(_draw);
	}
}

void Gameplay::Tile_Update(Player& player, Map_handler& map)//Handles changes involving map tiles
{
	change_tile = false;
	if((int)player.getTextPos().x % TILESIZE == 0 && (int)player.getTextPos().y % TILESIZE == 0)
	{
		change_tile = true;
	}

	//Water
	if((map.getTile(player.getTextPos()) == 0 || map.getTile(player.getTextPos()) == 2 || map.getTile(player.getTextPos()) == 3 || map.getTile(player.getTextPos()) == 10 || map.getTile(player.getTextPos()) == 16
		|| map.getTile(player.getTextPos()) == 12) && player.old_tile != 5 && change_tile == true)
	{
		map.setTile(player.getTextPos(),4);
		map.setObject(player.getTextPos(),0);
		change_ghost = true;
		tiles_changed++;
		audio.Play('W');
	}

	if(map.getTile(player.getTextPos()) == 17 && change_tile == true)
	{
		map.setTile(player.getTextPos(),4);
	}

	//Special tiles_________________________________________
	//Change_tile(player,5,3);

	//Lava
	if(map.getTile(player.getTextPos()) == 5 && change_tile == true)
	{
		map.setTile(player.getTextPos(),3);
		audio.Play('L');
	}

	//Ice
	if(map.getTile(player.getTextPos()) == 6 && player.old_tile != 7 && player.old_tile != 9 && change_tile == true)
	{
		map.setTile(player.getTextPos(),4);//set Ice to water
		change_ghost = true;
		tiles_changed++;
		audio.Play('I');
	}

	//Red Ice
	if(change_tile == true && map.getTile(player.getTextPos()) == 7)
	{
		map.setTile(player.getTextPos(),6);//set Red Ice to ice	
		audio.Play('I');
	}
	
	//Mirror Ice
	if(change_tile == true && map.getTile(player.getTextPos()) == 9)
	{
		if(audio.isPlaying() == false)
		{
			//audio.Play('I');
		}
	}


	//Change between ghost tiles
	if(change_ghost == true)
	{
		for(int y = 0; y < map.getMapSize().y/TILESIZE; y++)
		{
			for(int x = 0; x < map.getMapSize().x/TILESIZE; x++)
			{
				if(map.getObject(TILESIZE*x,TILESIZE*y) == 13)//Change ghost to transparent
				{
					map.setObject(TILESIZE*x,TILESIZE*y,0);
				}
				else if(map.getTile(TILESIZE*x,TILESIZE*y) == 12)
				{
					map.setObject(TILESIZE*x,TILESIZE*y,13);//Change transparent to ghost
					audio.Play('G');
				}
			}
		}
		change_ghost = false;
	}
	// Movement on ice________________________________________________
	if(map.getTile(player.getPos()) == 6 || map.getTile(player.getPos()) == 7 || map.getTile(player.getPos()) == 9)//Ice
	{
		//Move player over ice Tiles
		if(player.getMoveDir(UP) == true && player.getSpeed(UP) > 0)
		{
			player.old_tile = map.getTile(player.getPos().x, player.getPos().y-TILESIZE);
			player.movePlayerV(-player.getSpeed(UP));
			if(map.getTile((int)player.getPos().x,(int)player.getPos().y-TILESIZE) == 6 || map.getTile((int)player.getPos().x,(int)player.getPos().y-TILESIZE) == 7 
				|| map.getTile((int)player.getPos().x,(int)player.getPos().y-TILESIZE) == 9)
			{
				player.setMoveFinished(false);
			}
			
		}
		else if(player.getMoveDir(DOWN) == true && player.getSpeed(DOWN) > 0)
		{
			player.old_tile = map.getTile(player.getPos().x, player.getPos().y+TILESIZE);
			player.movePlayerV(player.getSpeed(DOWN));
			if(map.getTile((int)player.getPos().x,(int)player.getPos().y+TILESIZE) == 6 || map.getTile((int)player.getPos().x,(int)player.getPos().y+TILESIZE) == 7 
				|| map.getTile((int)player.getPos().x,(int)player.getPos().y+TILESIZE) == 9)
			{
				player.setMoveFinished(false);
			}
			
		}
		else if(player.getMoveDir(LEFT) == true && player.getSpeed(LEFT) > 0)
		{
			player.old_tile = map.getTile(player.getPos().x-TILESIZE, player.getPos().y);
			player.movePlayerH(-player.getSpeed(LEFT));
			if(map.getTile((int)player.getPos().x-TILESIZE,(int)player.getPos().y) == 6 || map.getTile((int)player.getPos().x-TILESIZE,(int)player.getPos().y) == 7 
				|| map.getTile((int)player.getPos().x-TILESIZE,(int)player.getPos().y) == 9)
			{
				player.setMoveFinished(false);
			}
		}
		else if(player.getMoveDir(RIGHT) == true && player.getSpeed(RIGHT) > 0)
		{
	
			player.old_tile = map.getTile(player.getPos().x+TILESIZE, player.getPos().y);
			player.movePlayerH(player.getSpeed(RIGHT));
			if(map.getTile((int)player.getPos().x+TILESIZE,(int)player.getPos().y) == 6 || map.getTile((int)player.getPos().x+TILESIZE,(int)player.getPos().y) == 7
				|| map.getTile((int)player.getPos().x+TILESIZE,(int)player.getPos().y) == 9)
			{
				player.setMoveFinished(false);
			}
		}
	}
	
	if(map.getTile(player.getPos()) != 6 && map.getTile(player.getPos()) != 7 && map.getTile(player.getPos()) != 9)
	{
		for(int i = 0; i < 4; i++)
		{
			player.setMoveDir(i,false);
		}
	}

}


void Gameplay::Initialize_level(std::string& map_names)//Does all the level initialization that must be done everytime level is started
{
	player = Player();
	map.Initialize(map_names);
	player.setPos(map.getPlayerStartPos());
	player.setTextPos(map.getPlayerStartPos());
	tiles_changed = 0;
	level_clear = false, change_ghost = false;
}

void Gameplay::Hud(Draw_handler& _draw)//Contains draw commands for level information and other things that are drawn on top of level
{
	int viewX = (int)camera->getWiew().getCenter().x;
	int viewY = (int)camera->getWiew().getCenter().y-SCREEN_HEIGHT/2;
	
	_draw.write(map.Map_name(),30,viewX-map.Map_name().size()/2*15,viewY,sf::Color::White);
	_draw.write("Tiles Remaining ",map.getTilesToWin()-tiles_changed,20,viewX+SCREEN_WIDTH/2-200,viewY,sf::Color::White);
	_draw.write("Goal ",map.getTilesToWin(),20,viewX+SCREEN_WIDTH/2-200,viewY+25,sf::Color::White);
	_draw.write("Tiles Changed ",tiles_changed,20,viewX+SCREEN_WIDTH/2-200,viewY+45,sf::Color::White);
}

void Gameplay::Level_clear_menu(Draw_handler& _draw)//Contains draw commands used to show the level clear menu
{
	_draw.Rectangle(sf::Vector2f(camera->getWiew().getCenter().x-160,camera->getWiew().getCenter().y-200),sf::Vector2f(0,800),300,200);
	_draw.write("LEVEL CLEAR!!!",30,camera->getWiew().getCenter().x-7*15,camera->getWiew().getCenter().y-200,sf::Color::Red);
	_draw.write("Press Space to",25,camera->getWiew().getCenter().x-8*12-1,camera->getWiew().getCenter().y-150,sf::Color::Yellow);
	_draw.write("advance",25,camera->getWiew().getCenter().x-4*12-1,camera->getWiew().getCenter().y-120,sf::Color::Yellow);
	_draw.write("to the next level",25,camera->getWiew().getCenter().x-9*12-1,camera->getWiew().getCenter().y-90,sf::Color::Yellow);
}