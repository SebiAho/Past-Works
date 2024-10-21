#pragma once
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Window.hpp>

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>

class Input//Contains functions for the game controlls
{
public:
	Input(void);
	~Input(void);

	//Keyboard
	static bool Hold_Key(sf::Keyboard::Key _key);//Returns true wehen key is held (Notes! Is here to keep all key functions in a single place)
	static bool Release_Key(sf::Keyboard::Key _key);//Returns a single instanse of true upon release of a key
	static bool Press_Key(sf::Keyboard::Key _key);//Returns a single instanse of true upon press of a key

	//Mouse
	static bool Hold_mouse(sf::Mouse::Button _button);//Returns true wehen key is held (Notes! Is here to keep all key functions in a single place)
	static bool Release_mouse(sf::Mouse::Button _button);//Returns a single instanse of true upon release of a key
	static bool Press_mouse(sf::Mouse::Button _button);//Returns a single instanse of true upon press of a key
	static sf::Vector2i Mouse_pos(sf::Window& _window);//Position of mouse cursor on the screen
	//Note! Code: "window.mapPixelToCoords(Input::Mouse_pos(window))" gives accurate mouse coordinates on level

private:
	static bool pressed[101], released[101];//sf::Keyboard::Key::KeyCount
	static bool m_pressed[5], m_released[5];//sf::Mouse::Button::ButtonCount
};