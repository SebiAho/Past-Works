#pragma once
#include <SFML\System.hpp>
#include "Draw_handler.h"

class Object_base//Base class for objects
{
public:
	
	virtual ~Object_base(void);

	virtual void Update();
	virtual void Draw(Draw_handler& _draw); 

	sf::Vector2f getPos(){ return pos; };
	void setPos(const sf::Vector2f& _pos){ pos = _pos; };
	void setPos(int _posX, int _posY){ pos.x = (float)_posX;	pos.y = (float)_posY; };

	sf::Vector2f getText(){ return text; };
	void setText(float _x, float _y) { pos.x = _x; pos.y = _y; };
	


protected:
	Object_base();
	sf::Vector2f pos;//object position
	sf::Vector2f text;//Location of object image on sprite map
};