#pragma once

#include "Object_base.h"
#include "Animation.h"
#include "Map_handler.h"

class Player:public Object_base//Class containing player specific code
{
public:
	Player(void);
	~Player(void);

	void Update(const sf::Time _time, Map_handler& current_tile);
	void Draw(Draw_handler& _draw);
	void Hud(Draw_handler& _draw, sf::Vector2f _defaultView);//Draws grid onto the screen (Separated from draw to ensure it is drawn last)
	
	//Getters and setter
	void setMoveFinished(bool finished){moveFinished = finished;};
	
	int getSpeed(int _direction){return (int)speed[_direction];};
	void setSpeed(int _direction, float _value){speed[_direction] = _value;};

	void movePlayerH(int speed){pos.x += speed;};
	void movePlayerV(int speed){pos.y += speed;};

	int getOldTile(){return old_tile;};
	void setOldTile(bool _value){old_tile = _value;};

	void setMoveDir(int _direction, bool _value){move_dir[_direction] = _value;};
	bool getMoveDir(int _direction){return move_dir[_direction];};

	void setTextPos(sf::Vector2f _pos){ text_pos = pos; };
	sf::Vector2f getTextPos(){return sf::Vector2f(text_pos.x,text_pos.y);};
	sf::Vector2f getTextPosF(){return text_pos;};

	int old_tile;
	bool hasMoved, moveFinished;
private:
	float side_col[4];//used by collision checking variables
	bool gridOn;//Determines if map grid is on or of
	float speed[4];//Player speed in x,y axis(0 = up, 1 = down, 2 = left, 3 = right)
	bool move_dir[4];//Direction = true if player has moved there(0 = up, 1 = down, 2 = left, 3 = right)
	
	Animation anim;
	sf::Vector2f text_pos;
};

