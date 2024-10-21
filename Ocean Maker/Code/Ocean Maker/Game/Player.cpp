#include "Player.h"
#include "Input.h"
#include "Base.h"

#include <iostream>

Player::Player(void) : hasMoved(false), gridOn(false), moveFinished(true), old_tile(0)
{
	pos.x = 0;
	pos.y = 0;
	text_pos = pos;

	text = sf::Vector2f(400,200);
	
	speed[0] = speed[1] = speed[2] = speed[3] = 100;
	move_dir[0] = move_dir[1] = move_dir[2] = move_dir[3] = false;
	
	anim = Animation(3,0.2f);
}


Player::~Player(void)
{
}

void Player::Update(const sf::Time _time, Map_handler& current_tile)
{
	hasMoved = false;
	anim.Update(_time.asSeconds());
	//Movement_____________________________________________
	if(moveFinished == true)
	{
		if(Input::Press_Key(sf::Keyboard::Up) || Input::Press_Key(sf::Keyboard::W))
		{ 
			text.x = 700;
			if(speed[UP] > 0)
			{
				old_tile = current_tile.getTile((int)pos.x, (int)pos.y-TILESIZE);
				pos.y -= speed[UP];
				move_dir[UP] = true; 
				move_dir[1] = move_dir[2] = move_dir[3] = false;
				hasMoved = true;
			}
		}

		else if(Input::Press_Key(sf::Keyboard::Down) || Input::Press_Key(sf::Keyboard::S))
		{ 
			text.x = 400;
			if(speed[DOWN] > 0)
			{
				old_tile = current_tile.getTile((int)pos.x, (int)pos.y+TILESIZE);
				pos.y += speed[DOWN]; 
				move_dir[DOWN] = true; 
				move_dir[0] = move_dir[2] = move_dir[3] = false;
				hasMoved = true;
			}
		}

		else if(Input::Press_Key(sf::Keyboard::Left) || Input::Press_Key(sf::Keyboard::A))
		{
			text.x = 500;
			if(speed[LEFT] > 0)
			{
				old_tile = current_tile.getTile((int)pos.x-TILESIZE, (int)pos.y);
				pos.x -= speed[LEFT]; 
				move_dir[LEFT] = true; 
				move_dir[0] = move_dir[1] = move_dir[3] = false;
				hasMoved = true;
			}
		}

		else if(Input::Press_Key(sf::Keyboard::Right) || Input::Press_Key(sf::Keyboard::D))
		{ 
			text.x = 600;
			if(speed[RIGHT] > 0)
			{
				old_tile = current_tile.getTile((int)pos.x+TILESIZE, (int)pos.y);
				pos.x += speed[RIGHT];
				move_dir[RIGHT] = true;
				move_dir[0] = move_dir[1] = move_dir[2] = false;
				hasMoved = true;
			}
		}
	}

	//Movement animation
	if(text_pos.x < pos.x)
	{
		text.y = 200+200*anim.getIndex();
		text_pos.x += 10;
		moveFinished = false;
	}
	if(text_pos.x > pos.x)
	{
		text.y = 200+200*anim.getIndex();
		text_pos.x -= 10;
		moveFinished = false;
	}

	if(text_pos.y < pos.y)
	{
		text.y = 200+200*anim.getIndex();
		text_pos.y += 10;
		moveFinished = false;
	}

	if(text_pos.y > pos.y)
	{
		text.y = 200+200*anim.getIndex();
		text_pos.y -= 10;
		moveFinished = false;
	}

	if(text_pos == pos)
	{
		moveFinished = true;
		text.y = 200;
	}
	if(moveFinished == false)
		{
//			std::cout<<getHasMoved()<<"r \n";std::cout<<getTextPos().x<<" "<<getTextPos().y<<"\n";
		}
	speed[0] = speed[1] = speed[2] = speed[3] = 100;//Reset the speed values

	//Grid_________________________________________________
	if(Input::Press_Key(sf::Keyboard::Space))
	{
		if( gridOn == false)
		{
			gridOn = true;
		}
		else
		{
			gridOn = false;
		}
	}
}

void Player::Draw(Draw_handler& _draw)
{
	_draw.Rectangle(sf::Vector2f(text_pos.x,text_pos.y-TILESIZE),text,TILESIZE,TILESIZE*2);
}

void::Player::Hud(Draw_handler& _draw, sf::Vector2f _defaultView)
{

	//Game grid
	if(gridOn == true)
	{
		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 10; x++)
			{
				_draw.Rectangle(sf::Vector2f(_defaultView.x - SCREEN_WIDTH/2 + TILESIZE*x,_defaultView.y - SCREEN_HEIGHT/2 + TILESIZE*y),sf::Vector2f(100,0));
			}
		}		
	}
}