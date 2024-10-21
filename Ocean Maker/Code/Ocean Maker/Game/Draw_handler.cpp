#include "Draw_handler.h"
#include "Base.h"

#include <iostream>

int Draw_handler::vertexCount = 0;
Draw_handler::Draw_handler(sf::RenderWindow& _window):window(_window)
{
	Load_texture();
	ScreenContent.setPrimitiveType(sf::Triangles);
}


Draw_handler::~Draw_handler(void)
{
}

int Draw_handler::Load_texture()//Loads textures, returns the number of succesfully loaded textures
{
	int text_loaded = 0;

	if(texture.loadFromFile("Resources/Tiles_Base.png"))
	{
		text_loaded++;
	}

	return text_loaded;
}

void Draw_handler::Draw()//Draws the ScreenContent and Text into the screen
{
	window.clear();
	window.draw(ScreenContent, &texture);

	
	for(int i = 0; i < write.getTextArraySize(); i++)//Draw text graphics
	{
		window.draw(write.getText(i));
	}
	write.clear_array();//Clear the text array

	window.display();
	vertexCount = 0;
}

void Draw_handler::Rectangle(sf::Vector2f _pos, sf::Vector2f _text)//Adds a tile rectangle onto ScreenContent (heigth & width = TILESIZE)
{
	Rectangle(_pos,_text,TILESIZE,TILESIZE);
}

void Draw_handler::Rectangle(sf::Vector2f _pos, sf::Vector2f _text, int _width, int _height)//Adds a textured rectangle onto the ScreenContent
{
	vertexCount = vertexCount + 6;
	ScreenContent.resize(vertexCount);
	//Position
	ScreenContent[vertexCount -6].position = sf::Vector2f(_pos.x,_pos.y+_height);//Lower Left Corner
	ScreenContent[vertexCount -5].position = _pos;//Upper Left Corner
	ScreenContent[vertexCount -4].position = sf::Vector2f(_pos.x + _width,_pos.y);//Upper Right Corner
	
	ScreenContent[vertexCount -3].position = sf::Vector2f(_pos.x + _width, _pos.y + _height);//Lower Right Corner
	ScreenContent[vertexCount -2].position = sf::Vector2f(_pos.x, _pos.y + _height);//Lower Left Corner
	ScreenContent[vertexCount -1].position = sf::Vector2f(_pos.x + _width,_pos.y);//Upper Left Corner

	//Texture location
	ScreenContent[vertexCount -6].texCoords = sf::Vector2f(_text.x, _text.y + _height);//Lower Left Corner
	ScreenContent[vertexCount -5].texCoords = _text;//Upper Left Corner
	ScreenContent[vertexCount -4].texCoords = sf::Vector2f(_text.x + _width, _text.y);//Upper Right Corner

	ScreenContent[vertexCount -3].texCoords = sf::Vector2f(_text.x + _width, _text.y + _height);//Lower Right Corner
	ScreenContent[vertexCount -2].texCoords = sf::Vector2f(_text.x,_text.y + _height);//Right Left Corner
	ScreenContent[vertexCount -1].texCoords = sf::Vector2f(_text.x + _width, _text.y);//Upper Right Corner
}
void Draw_handler::Triangle(sf::Vector2f _pos, sf::Vector2f _text)//Adds a textured triangle onto the ScreenContent
{
	vertexCount = vertexCount + 3;
	ScreenContent.resize(vertexCount);
	//Position
	ScreenContent[vertexCount -3].position = sf::Vector2f(_pos.x,_pos.y+ TILESIZE);//Lower Left Corner
	ScreenContent[vertexCount -2].position = _pos;//Upper Left Corner
	ScreenContent[vertexCount -1] = sf::Vector2f(_pos.x+TILESIZE,_pos.y);//Upper Right Corner

	//Texture
	ScreenContent[vertexCount -3].texCoords = sf::Vector2f(_text.x, _text.y+ TEXTSIZE);//Lower Left Corner
	ScreenContent[vertexCount -2].texCoords = _text;//Upper Left Corner
	ScreenContent[vertexCount -1].texCoords = sf::Vector2f(_text.x + TEXTSIZE, _text.y);//Upper Right Corner
}