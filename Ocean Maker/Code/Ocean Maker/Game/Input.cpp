#include "Input.h"

#include <iostream>

bool Input::pressed[] = {false};
bool Input::released[] = {false};
bool Input::m_pressed[] = {false};
bool Input::m_released[] = {false};

Input::Input(void)
{

}


Input::~Input(void)
{
}
//Keyboard______________________________________________________________
bool Input::Hold_Key(sf::Keyboard::Key _key)//Returns true wehen key is held (Notes! Is here to keep all key functions in a single place)
{
	return sf::Keyboard::isKeyPressed(_key);
}

bool Input::Press_Key(sf::Keyboard::Key _key)//Returns a single instanse of true upon press of a key
{
	bool result = false;

	if(sf::Keyboard::isKeyPressed(_key) == true && pressed[_key] == false)
	{
		pressed[_key] = true;
		result = true;
	}

	if(sf::Keyboard::isKeyPressed(_key) == false && pressed[_key] == true)
	{
		pressed[_key] = false;
	}
	return result;
}

bool Input::Release_Key(sf::Keyboard::Key _key)//Returns a single instanse of true upon release of a key
{
	bool result = false;

	if(sf::Keyboard::isKeyPressed(_key) == true)
	{
		released[_key] = true;//Merkitsee näppäimen painetuksi
	}

	if(sf::Keyboard::isKeyPressed(_key) == false && released[_key] == true)//Tarkastaa että näppäin on vapautettu
	{
		released[_key] = false;
		result = true;
	}
	return result;
}

//Mouse____________________________________________________________________________
bool Input::Hold_mouse(sf::Mouse::Button _button)//Returns true wehen key is held (Notes! Is here to keep all key functions in a single place)
{
	return sf::Mouse::isButtonPressed(_button);
}

bool Input::Press_mouse(sf::Mouse::Button _button)//Returns a single instanse of true upon press of a key
{
	bool result = false;

	if(sf::Mouse::isButtonPressed(_button) == true && m_pressed[_button] == false)
	{
		m_pressed[_button] = true;
		result = true;
	}

	if(sf::Mouse::isButtonPressed(_button) == false && m_pressed[_button] == true)
	{
		m_pressed[_button] = false;
	}
	return result;
}

bool Input::Release_mouse(sf::Mouse::Button _button)//Returns a single instanse of true upon release of a key
{
	bool result = false;

	if(sf::Mouse::isButtonPressed(_button) == true)
	{
		m_pressed[_button] = true;//Merkitsee näppäimen painetuksi
	}

	if(sf::Mouse::isButtonPressed(_button) == false && m_pressed[_button] == true)//Tarkastaa että näppäin on vapautettu
	{

		m_pressed[_button] = false;
		result = true;
	}
	return result;
}

//Mouse position
sf::Vector2i Input::Mouse_pos(sf::Window& _window)//Position of mouse cursor on the screen
{
	return sf::Mouse::getPosition(_window);
}
