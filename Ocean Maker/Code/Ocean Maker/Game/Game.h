#pragma once
#include "Gameplay.h"
#include "Draw_handler.h"
#include "Camera.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics.hpp>

#include <vector>
#include <string>

class Game//Contains the gameloop and handles basic initialization
{
public:
	Game(void);
	~Game(void);

	void Update();//Holds the main loop, gamestates and handles basic initialisation and events

private:
	int gamestate, map_amount;
	sf::RenderWindow main_window;

	void Greate_window();//Intitalizes the values of the main window

	std::vector<std::string> map_names;

};

