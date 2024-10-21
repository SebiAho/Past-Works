#include "InputSystem.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include <cmath>

InputSystem::InputSystem(sf::Window& _window) : System(Sys::INPUT), window(_window), mouse_wheel_pos(0), mouse_click(false), mouse_moved(false), angle(0.0f)
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::Initialize()
{

}

void InputSystem::Update(GameObject& _object)
{
	if (use == true)
	{
		if (mouse_moved == true)
			mouse_pos = sf::Mouse::getPosition(window);	
	}
	if (_object.getOn() && _object.getComponent(Comp::INPUT) != nullptr)
	{
		for (int i = 0; i < InpComponent(_object)->input.size(); ++i)
		{
			//Set the position of objects to mousewheel position
			int b = InpComponent(_object)->input.at(i);
			if (b == 1 && _object.getComponent(Comp::TRANS) != nullptr)
			{
				if (mouse_pos.y > 15 && mouse_pos.y < 522)
					TransComponent(_object)->position.y = mouse_pos.y;
			}

			//Point object towards mouse
			if (b == 2 && _object.getComponent(Comp::TRANS) != nullptr)
			{
				angle = getAngle(TransComponent(_object)->position, sf::Vector2f(TransComponent(_object)->position.x + 10, TransComponent(_object)->position.y + mouse_wheel_pos));

				TransComponent(_object)->transform.setPosition(TransComponent(_object)->position.x + 5.0, TransComponent(_object)->position.y + TransComponent(_object)->size.y*0.5);//Adjust position
				TransComponent(_object)->transform.setOrigin(TransComponent(_object)->position.x + 5.0, TransComponent(_object)->position.y + TransComponent(_object)->size.y*0.5);//Set rotation point
				TransComponent(_object)->transform.setRotation(angle * 180 / 3.14159265f);//Set rotation, (setRotate(float angle) requires radians to be converted to degrees)

			}
		}
	}

	//Reset values
	if (use == true)
	{
		mouse_moved = false;
		mouse_click = false;
	}
}

void InputSystem::HandleMessages(sf::Event& _event)
{
	int i = 0;
	//Get change mouse_wheel_pos value when mouse wheel moves
	if (_event.type == sf::Event::MouseWheelMoved)
	{
		if (_event.mouseWheel.delta > 0 && mouse_wheel_pos >= -190)
			mouse_wheel_pos--;
		
		if (_event.mouseWheel.delta < 0 && mouse_wheel_pos <= 190)
			mouse_wheel_pos++;
	}

	//get mouse click
	if (_event.type == sf::Event::MouseButtonReleased)
	{
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			mouse_click = true;
		}
	}

	//get mouse moved
	if (_event.type == sf::Event::MouseMoved)
	{
		mouse_moved = true;
	}
}

float InputSystem::getAngle(sf::Vector2f _posA, sf::Vector2f _posB)
{
	return atan2(_posB.y - _posA.y, _posB.x - _posA.x);
}