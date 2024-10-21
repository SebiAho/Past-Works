#include "RendererSFML.h"

using namespace seb;

RendererSFML::RendererSFML()
{
}


RendererSFML::~RendererSFML()
{
}

void RendererSFML::BeginDraw(sf::RenderWindow& _window, sf::Color _clearColor)
{
	_window.clear(_clearColor);
}

void RendererSFML::Draw(sf::RenderWindow& _window, GraphicsComponent* _component)
{
	if (_component->getOn() == true)
	{
		_window.draw(_component->sprite);
	}
}

void RendererSFML::EndDraw(sf::RenderWindow& _window)
{
	_window.display();
}