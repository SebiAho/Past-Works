#include "Game_Logic.h"
#include <time.h>

Game_Logic::Game_Logic()
{
	Init();
}

Game_Logic::~Game_Logic()
{
}

void Game_Logic::Update(Graphic_Object& _box, Renderer& _renderer, GTexture& _texture, Android_Engine& _engine, float _player_x)
{
	if (reset == false)
	{

		for (int i = 0; i < block_amount; i++)
		{
			block_z[i] += speed*speed_multiplier;
			
			if (block_z[i] > player_y)
			{
				block_z[i] = start_pos - 400 * block_amount;

				srand(Time_ms());
				random = rand() % 2 + 1;
				if (random == 1)
					block_x[i] = 25 * random;
				else
					block_x[i] = -25 * random;

				speed_multiplier += 0.25;
				if (i == block_amount)
				{
					speed_multiplier += 0.25;
				}

				if (block_x[i] == _player_x)
				{
					reset = true;
				}

				srand(Time_ms());
				if (clear_color < 1.0f)
				{
					clear_color += 0.01f;
				}

				_renderer.setClear_color(clear_color, 0.0f, 0.0f, 1.0f);
			}
			_box.Move(0.0f, block_x[i], block_z[i]);
			_renderer.Draw(_box, _texture, _engine);

		}


	}
	else
	{
		Init();
	}
}

void Game_Logic::Init()
{
	srand(Time_ms());

	player_y = 100.0f;

	start_pos = -50.0f;
	speed = 0.5f;
	speed_multiplier = 1.0f;

	for (int i = 0; i < block_amount; i++)
	{
		block_z[i] = start_pos - 400*i;
		random = rand() % 2 + 1;
		if (random == 1)
			block_x[i] = 25 * random;
		else
			block_x[i] = -25 * random;
	}

	reset = false;
}

double Game_Logic::Time_ms()
{
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return 1000.0 * res.tv_sec + static_cast<double>(res.tv_nsec) / 1e6;
}

