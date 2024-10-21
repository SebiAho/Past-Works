#pragma once

#include <SFML\Graphics.hpp>

class Editor_camera
{
public:
public:
	Editor_camera(sf::RenderWindow& _window);
	~Editor_camera(void);

	void Update(sf::Vector2f pos, sf::Vector2i _mapSize);
	sf::View getWiew();
	void setWiew(sf::View _view);

private:
	sf::View GameView;
	sf::RenderWindow& window;
};

