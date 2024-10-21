#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#include "Font_handler.h"

class Draw_handler//Class that handless drawing functions
{
public:
	Draw_handler(sf::RenderWindow& _window);
	~Draw_handler(void);

	void Draw();//Draws the ScreenContent and Text into the screen
	void Triangle(sf::Vector2f _pos, sf::Vector2f _text);//Adds a textured triangle onto the ScreenContent
	void Rectangle(sf::Vector2f _pos, sf::Vector2f _text, int _width, int _height);//Adds a textured rectangle onto the ScreenContent
	void Rectangle(sf::Vector2f _pos, sf::Vector2f _text);//Adds a tile rectangle onto ScreenContent (heigth & width = TILESIZE)
	Font_handler write;//Font handler class
private:
	sf::Texture texture;
	sf::RenderWindow& window;

	sf::VertexArray ScreenContent;//Array used to draw most stuff on the screen
	
	static int vertexCount;//Size of the ScreenContent array
	int Load_texture();//Loads textures, returns the number of succesfully loaded textures
	
};

