#include "Editor_camera.h"

#include "Base.h"

Editor_camera::Editor_camera(sf::RenderWindow& _window):window(_window)
{
}


Editor_camera::~Editor_camera(void)
{
}

void Editor_camera::Update(sf::Vector2f pos, sf::Vector2i _mapSize)
{
	GameView.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	sf::Vector2f cameraPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

	cameraPos.x = pos.x + TILESIZE;
	cameraPos.y = pos.y + TILESIZE;

	GameView.setCenter(cameraPos);
	window.setView(GameView);

}

sf::View Editor_camera::getWiew()
{
	return GameView;
}

void Editor_camera::setWiew(sf::View _view)
{
	window.setView(_view);
}

