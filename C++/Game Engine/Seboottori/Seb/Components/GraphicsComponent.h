#pragma once
#include "../System/Component.h"
#include "../3rd_party/SFML/SFML/Graphics/Sprite.hpp"
namespace seb
{
	class GraphicsComponent: public Component
	{
	public:
		GraphicsComponent();
		~GraphicsComponent();

		sf::Sprite sprite; //(Note: Will be replaced with a vertex array based solution eventually)
	};
}
