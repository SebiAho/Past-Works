#include "GraphicsSystem.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"

#include <string>
#include <cassert>



GraphicsSystem::GraphicsSystem(sf::RenderWindow& _window) :System(Sys::GRAPHIC), window(_window), clear_color(sf::Color::Black)
{
	_window.setFramerateLimit(60);
}

GraphicsSystem::~GraphicsSystem()
{
}

//System functions
void GraphicsSystem::Initialize()
{
}

void GraphicsSystem::Update(GameObject& _object)
{
	//Update position
	if (_object.getComponent(Comp::TRANS) != nullptr && _object.getComponent(Comp::REND) != nullptr)
	{
		RendComponent(_object)->shape[0].position = TransComponent(_object)->position;
		RendComponent(_object)->shape[1].position = sf::Vector2f(TransComponent(_object)->position.x, TransComponent(_object)->position.y + TransComponent(_object)->size.y);
		RendComponent(_object)->shape[2].position = sf::Vector2f(TransComponent(_object)->position.x + TransComponent(_object)->size.x, TransComponent(_object)->position.y);
		RendComponent(_object)->shape[3].position = TransComponent(_object)->position + TransComponent(_object)->size;
	}
}

void GraphicsSystem::HandleMessages(sf::Event& _event)
{
	if (_event.type == sf::Event::Closed)
	{
		window.close();
	}
}

//Render functions
void GraphicsSystem::BeginDraw()
{
	window.clear(clear_color);
}

void GraphicsSystem::Draw(GameObject& _object)
{
	if (_object.getOn() && _object.getComponent(Comp::TRANS) != nullptr && _object.getComponent(Comp::REND) != nullptr)
	{
		RendComponent(_object)->state.transform = TransComponent(_object)->transform.getTransform();
		window.draw(RendComponent(_object)->shape, RendComponent(_object)->state);
	}
}

void GraphicsSystem::StaticDraw(GameObject& _object)
{
	if (_object.getOn() && _object.getComponent(Comp::REND) != nullptr)
	{
		window.draw(RendComponent(_object)->shape, &RendComponent(_object)->texture);
	}
}

void GraphicsSystem::DrawGameText(GameObject& _object)
{
	if (_object.getOn() && _object.getComponent(Comp::TEXT) != nullptr)
	{
		window.draw(FontComponent(_object)->text);
	}
}

void GraphicsSystem::EndDraw()
{
	window.display();
}

void GraphicsSystem::LoadTexture(GameObject& _object, std::string _texture)
{
	if (_object.getComponent(Comp::REND) != nullptr)
	{
		RendComponent(_object)->texture.loadFromFile("Assets\\"+_texture);
		RendComponent(_object)->state.texture = &RendComponent(_object)->texture;
	}
}

void GraphicsSystem::AddShape(GameObject& _object, sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _texturesize)
{
	if (_object.getComponent(Comp::REND) != nullptr)
	{
		RendComponent(_object)->shape = sf::VertexArray(sf::TrianglesStrip, 4);
		RendComponent(_object)->shape[0].position = _pos;
		RendComponent(_object)->shape[1].position = sf::Vector2f(_pos.x, _pos.y + _size.y);
		RendComponent(_object)->shape[2].position = sf::Vector2f(_pos.x + _size.x, _pos.y);
		RendComponent(_object)->shape[3].position = _pos + _size;

		RendComponent(_object)->shape[0].texCoords = sf::Vector2f(0, 0);
		RendComponent(_object)->shape[1].texCoords = sf::Vector2f(0, _texturesize.y);
		RendComponent(_object)->shape[2].texCoords = sf::Vector2f(_texturesize.x, 0);
		RendComponent(_object)->shape[3].texCoords = _texturesize;
	}
}

void GraphicsSystem::AddShape(GameObject &_object)
{
	if (_object.getComponent(Comp::TRANS) != nullptr && _object.getComponent(Comp::REND) != nullptr)
	{
		AddShape(_object, TransComponent(_object)->position, TransComponent(_object)->size, sf::Vector2f(RendComponent(_object)->texture.getSize()));
	}
}

void GraphicsSystem::LoadFont(GameObject &_object, std::string _font)
{
	if (_object.getComponent(Comp::TEXT) != nullptr)
	{
		FontComponent(_object)->font.loadFromFile("Assets\\" + _font);
		FontComponent(_object)->text.setFont(FontComponent(_object)->font);
	}
}

void GraphicsSystem::SetText(GameObject &_object)
{
	if (_object.getComponent(Comp::TEXT) != nullptr)
	{
		FontComponent(_object)->text.setString(FontComponent(_object)->content);
	}
}