#include "GraphicsSystem.h"

using namespace seb;

GraphicsSystem::GraphicsSystem() : System((unsigned int)SYS::GRAPHICS), window_size(800,600), name("Window"), clear_color(sf::Color::Black), style(7)
{
}

GraphicsSystem::~GraphicsSystem()
{
}

void GraphicsSystem::Intitialize(ObjectManager &_objects)
{
	//Make sure components used by the system have a handler (Note: AddHandler() will automatically check for duplicate handlers)
	//_components.addHandler((unsigned int)COMP::TRANSFORM);
	//_components.addHandler((unsigned int)COMP::GRAPHICS);

	//Add references to pointers
	objects = &_objects;

	//Make sure system has handler for graphic components
	if (objects->getCompManager().getCompTypeSum() & (unsigned int)COMP::GRAPHICS)
		graphic_comps = &_objects.getCompManager().getHandler(COMP::GRAPHICS);
	else
	{
		_objects.getCompManager().addHandler(COMP::GRAPHICS);
		graphic_comps = &_objects.getCompManager().getHandler(COMP::GRAPHICS);
	}

}

void GraphicsSystem::Update()
{
	loop_number++;
	//gCast(objects->GetObject(0), COMP::GRAPHICS)->sprite.setTexture(test_texture);

	//Check if Graphics component handler is in use
	if (!objects->getCompManager().getHandler(COMP::GRAPHICS).getInUse())
		return;

	//Set transform
	if (objects->getCompManager().getHandler(COMP::TRANSFORM).getInUse())
	{
		//Set position
		for (std::vector<Object*>::iterator it = objects->getObjectsBegin(); it != objects->getObjectsEnd(); ++it)
		{
			if (((*it)->getCompTypeSum() & ((unsigned int)COMP::TRANSFORM) + (unsigned int)COMP::GRAPHICS))//Check that object has transform and graphic components
			{
				//setTransform(*it);
				//InitGraphicComp(gCast((*it)->getComponent(COMP::TRANSFORM)), "Background2.png");
			}
		}
	}

	//Draw
//	renderer.BeginDraw(window, clear_color);
	window.clear(clear_color);
	for (std::vector<Component*>::iterator it = graphic_comps->getComponentsBegin(); it != graphic_comps->getComponentsEnd(); ++it)
	{
		//renderer.Draw(window, gCast(*it));
		//window.draw(test_sprite);
		//window.draw(gCast(&test_object, COMP::GRAPHICS)->sprite);
		//window.draw(gCast(objects->GetObject(0), COMP::GRAPHICS)->sprite);
	}
	window.display();
	//renderer.EndDraw(window);
}

void GraphicsSystem::handleMessage(MessageHandler &_messages)
{

}

void GraphicsSystem::SetWindowSettings(unsigned int _width, unsigned int _height, std::string _name, sf::Color _clearColor, _Uint32t _style)
{
	window_size.x = _width;
	window_size.y = _height;
	name = _name;
	style = _style;
	clear_color = _clearColor;

	if (window.isOpen() == true)
	{
		window.close();
		window.create(sf::VideoMode(window_size.x, window_size.y), name, style);
	}
}

void GraphicsSystem::InitGraphicComp(GraphicsComponent* _comp, std::string _texture, sf::IntRect _area, sf::Color _color)
{
	
	_comp->sprite.setTexture(assets.getTexture(_texture));
	_comp->sprite.setTextureRect(_area);
	_comp->sprite.setColor(_color);
	_comp->setOn(true);
}

void GraphicsSystem::InitGraphicComp(Object* _ob, std::string _texture, sf::IntRect _area, sf::Color _color)
{
	if (_ob->getCompTypeSum() & (unsigned int)COMP::GRAPHICS)
	{
		InitGraphicComp(gCast(_ob->getComponent(COMP::GRAPHICS)), _texture, _area, _color);
	}
}

void GraphicsSystem::setTransform(Object *_object)
{
	gCast(_object, COMP::GRAPHICS)->sprite.setPosition(sf::Vector2f(tCast(_object, COMP::TRANSFORM)->position.x, tCast(_object, COMP::TRANSFORM)->position.y));
	
	/* What the previous looks like without a casting class
	static_cast<GraphicsComponent*>(_object->getComponent(COMP::GRAPHICS))->sprite.setPosition(sf::Vector2f(
		static_cast<TransformComponent*>(_object->getComponent(COMP::TRANSFORM))->position.x, 
		static_cast<TransformComponent*>(_object->getComponent(COMP::TRANSFORM))->position.y)
		);*/
}
