#pragma once

#include <SFML\Graphics.hpp>

class Camera
{
public:
	Camera(void);
	Camera(sf::RenderWindow& _window);
	~Camera(void);

	void Update(sf::Vector2f pos, sf::Vector2i _mapSize);
	sf::View getWiew();
	void setWiew(sf::View _view);
private:
	sf::View GameView;
	sf::RenderWindow& window;
};

