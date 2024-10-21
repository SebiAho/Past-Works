#pragma once
#include <System.h>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <vector>

#define InputSys(x, i) dynamic_cast<InputSystem*>(x.GetSystem(i))

class InputSystem : public System
{
public:
	InputSystem(sf::Window& _window);
	~InputSystem();

	//System functions
	void Initialize();
	void Update(GameObject& _object);
	void HandleMessages(sf::Event& _event);

	void PointToMouse(GameObject& _object);//rotates object to point towards mouse

	float getAngle(sf::Vector2f _posA, sf::Vector2f _posB);//Returns the angle between two positions in radians
	float getAngle(){ return angle; };//Return angle set in input update

	sf::Vector2i getMousePos(){ return mouse_pos; };
	

private:
	sf::Vector2i mouse_pos;
	sf::Window& window;
	int mouse_wheel_pos;
	bool mouse_click, mouse_moved;
	float angle;
};

