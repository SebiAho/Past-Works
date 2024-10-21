#pragma once
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\Rect.hpp>

#include "Player.h"
#include "Draw_handler.h"
#include "Camera.h"
#include "Map_handler.h"

#include "Animation.h"
#include "Audio_handler.h"

class Gameplay//Handless interraction between objects
{
	
public:
	Gameplay(sf::IntRect _bounds, sf::RenderWindow& _window);
	~Gameplay(void);

	Player player;
	Map_handler map;
	void Update(const sf::Time& _time, Draw_handler& _draw, int& _gamestate);//Handles any changes to level/player done after initialization
	void Initialize_level(std::string& map_name);//Does all the level initialization that must be done everytime level is started

private:
	sf::Time time;
	sf::IntRect bounds;
	sf::RenderWindow& window;
	Camera* camera;
	Audio_handler audio;

	int tiles_changed;//Amount of tiles player has changed to water
	void Hud(Draw_handler& _draw);//Contains draw commands for level information and other things that are drawn on top of level
	void Level_clear_menu(Draw_handler& _draw);//Contains draw commands used to show the level clear menu

	void Tile_Update(Player& player, Map_handler& map);//Handles changes involving map tiles
	bool change_tile, level_clear,change_ghost;
};

