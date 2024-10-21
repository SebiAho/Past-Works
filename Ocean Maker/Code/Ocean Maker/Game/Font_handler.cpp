#include "Font_handler.h"
#include <sstream>

Font_handler::Font_handler()
{
	Load_font();
}


Font_handler::~Font_handler(void)
{
}

//Load fonts from file_________________________________________________________________________
int Font_handler::Load_font()
{
	int fonts_loaded = 0;
	if(font.loadFromFile("Resources/RujisHandwritingFontv.2.0.otf"))
	{
		fonts_loaded++;
	}
	return fonts_loaded;
}

//Default colored text graphics______________________________________________________________
void Font_handler::operator()(std::string _text, int _size, int _posX, int _posY)
{
	sf::Text t(_text,font);
	t.setCharacterSize(_size);
	t.setPosition(sf::Vector2f((float)_posX,(float)_posY));
	text_array.push_back(t);
}

//Default colored text & number graphics______________________________________________________________
void Font_handler::operator()(std::string _text, int _num, int _size, float _posX, float _posY)
{
	//Change int into string
	std::stringstream stream;
	stream << _text << _num;
	
	sf::Text t(stream.str(),font);
	t.setCharacterSize(_size);
	t.setPosition(sf::Vector2f(_posX,_posY));

	text_array.push_back(t);
}

//Custom colored text graphics______________________________________________________________
void Font_handler::operator()(std::string _text, int _size, int _posX, int _posY, sf::Color _color)
{
	sf::Text t(_text,font);
	t.setCharacterSize(_size);
	t.setPosition(sf::Vector2f((float)_posX,(float)_posY));
	t.setColor(_color);

	text_array.push_back(t);
}

//Custom colored text & number graphics______________________________________________________________
void Font_handler::operator()(std::string _text, int _num, int _size, int _posX, int _posY, sf::Color _color)
{
	//Change int into string
	std::stringstream stream;
	stream << _text << _num;
	
	sf::Text t(stream.str(),font);
	t.setCharacterSize(_size);
	t.setPosition(sf::Vector2f((float)_posX,(float)_posY));
	t.setColor(_color);

	text_array.push_back(t);
}

//Clear array call
void Font_handler::clear_array()
{
	text_array.clear();
}

//Getter Methods____________________________________
sf::Text Font_handler::getText(int i)
{
	return text_array.at(i);
}

int Font_handler::getTextArraySize()
{
	return text_array.size();
}