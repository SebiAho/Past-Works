#pragma once
#include <string>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>

class Font_handler//Class containing methods used to display text
{
public:
	Font_handler();
	~Font_handler(void);

	void operator()(std::string _text, int _size, int _posX, int _posY);//Default colored text graphics
	void operator()(std::string _text, int _num, int _size, float _posX, float _posY);//Default colored text & number graphics

	void operator()(std::string _text, int _size, int _posX, int _posY, sf::Color _color);//Custom colored text graphics
	void operator()(std::string _text, int _num, int _size,  int, int _posY, sf::Color _color);//Custom colored text & number graphics

	void clear_array();//Clear array call

	//Getter Methods
	sf::Text getText(int i);
	sf::Font getFont(){return font;};
	int getTextArraySize();
private:
	int Load_font();//Load fonts from file
	sf::Font font;//Default font
	std::vector<sf::Text> text_array;//contains the text graphics to be drawn
};

