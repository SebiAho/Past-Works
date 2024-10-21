#include "Camera.h"
#include "Base.h"

Camera::Camera(void) :window(sf::RenderWindow())
{
}

Camera::Camera(sf::RenderWindow& _window):window(_window)
{
}


Camera::~Camera(void)
{
}

void Camera::Update(sf::Vector2f pos, sf::Vector2i _mapSize)
{
	GameView.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	sf::Vector2f cameraPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

	if(_mapSize.x > SCREEN_WIDTH)
	{
		cameraPos.x = pos.x + TILESIZE;
		//Camera borders

		//Check if horizontal camera movement is needed
		if(pos.x + TILESIZE < SCREEN_WIDTH/2)//middlepoint of player is less than middlepoint of screen
		{
			cameraPos.x = SCREEN_WIDTH/2;
		}
		if(pos.x + TILESIZE > _mapSize.x - SCREEN_WIDTH/2)
		{
			cameraPos.x = _mapSize.x - SCREEN_WIDTH/2;
		}
	}
	
	//Check if vertical camera movement is needed
	if(_mapSize.y > SCREEN_HEIGHT)
	{
		cameraPos.y = pos.y + TILESIZE;
		if(pos.y + TILESIZE < SCREEN_HEIGHT/2)
		{
			cameraPos.y = SCREEN_HEIGHT/2;
		}
		if(pos.y + TILESIZE > _mapSize.y - SCREEN_HEIGHT/2)
		{
			cameraPos.y = _mapSize.y - SCREEN_HEIGHT/2;
		}
	}
	GameView.setCenter(cameraPos);
	window.setView(GameView);

}

sf::View Camera::getWiew()
{
	return GameView;
}

void Camera::setWiew(sf::View _view)
{
	window.setView(_view);
}

