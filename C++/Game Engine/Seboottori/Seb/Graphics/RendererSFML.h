#pragma once
#include "../3rd_party/SFML/SFML/Graphics/RenderWindow.hpp"
#include "../Components/GraphicsComponent.h"
#include "Renderer.h"

namespace seb
{
	class RendererSFML:Renderer//SFML based renderer class
	{
	public:
		RendererSFML();
		~RendererSFML();

		void BeginDraw(sf::RenderWindow& _window, sf::Color _clearColor);
		void Draw(sf::RenderWindow& _window, GraphicsComponent *_component);//Draw component, (Note: Will be replaced with a vertex array based solution eventually)
		void EndDraw(sf::RenderWindow& _window);

	private:
		

	};
}
