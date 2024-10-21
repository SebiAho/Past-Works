#pragma once
#include <SFML\System.hpp>
#include "GraphicsSystem.h"
#include "SystemManager.h"

class Program
{
public:
	Program();
	~Program();

	void Loop();

	void InitializeLevel(int _level, SystemManager& _manager, int _rendId, int _physId);
	void UpdateText(SystemManager& _manager, int _rendId, float _angle, float _gravity);
	void DrawLevel(SystemManager& _manager, int _rendId);

private:
	sf::Vector2i window_size;
	int object_amount, text_amount, attempts, level;
	float force;//force the ball is launched
	bool in_basket;
};

