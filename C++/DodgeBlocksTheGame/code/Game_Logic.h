#pragma once
#include "Graphic_Object.h"
#include "Renderer.h"
#include "Android_Engine.h"
#include "glm/glm.hpp"
#include <stdlib.h> 

class Game_Logic//Contains advanced game logic
{
public:
	Game_Logic();
	~Game_Logic();

	void Update(Graphic_Object& _box, Renderer& _renderer, GTexture& _texture, Android_Engine& _engine, float _player_x);
	void Init();//Init the values to start
	static double Time_ms();//Get time in milliskeconds

private:
	static const int block_amount = 4;
	bool reset;
	int player_y;//player position
	int random;
	float start_pos, speed, speed_multiplier, clear_color;
	float block_x[block_amount], block_z[block_amount];//Block positions
};