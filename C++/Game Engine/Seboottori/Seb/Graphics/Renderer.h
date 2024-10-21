#pragma once
#include "WindowHandler.h"
#include "../Components/GraphicsComponent.h"

namespace seb
{
	class Renderer//Base class for renderer classes
	{
	public:
		Renderer();
		~Renderer();

		virtual void BeginDraw(WindowHandler& _window){};
		virtual void Draw(WindowHandler& _window, GraphicsComponent *_component){};//Draw component, (Note: May be replaced with a more efficient solution eventually)
		virtual void EndDraw(WindowHandler& _window){};
	};
}
