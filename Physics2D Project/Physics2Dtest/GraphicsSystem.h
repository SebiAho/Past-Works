#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <System.h>
#include <vector>
#include "RenderComponent.h"

#define GraphicsSys(x, i) dynamic_cast<GraphicsSystem*>(x.GetSystem(i))

class GraphicsSystem :public System
{
public:
	GraphicsSystem(sf::RenderWindow &_window);
	~GraphicsSystem();

	//System functions
	void Initialize();
	void Update(GameObject& _object);
	void HandleMessages(sf::Event& _event);

	//Render system functions
	void BeginDraw();
	void Draw(GameObject& _object);//Draw a object
	void StaticDraw(GameObject& _object);//Draw object that lacks transform component (not affected by Update function)
	void DrawGameText(GameObject& _object);
	void EndDraw(); //Switch drawn objects to screen

	void LoadTexture(GameObject& _object, std::string _texture);
	void AddShape(GameObject& _object, sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _texturesize);
	void AddShape(GameObject &_object);
	void LoadFont(GameObject &_object, std::string _font);
	void SetText(GameObject &_object);//Set TextComponent.content as drawn text

	//Setter functions
	sf::RenderWindow& setSize(sf::Vector2u _size){ window.setSize(_size); };
	void setClearColor(sf::Color _color){clear_color = _color;};

	//Getter functions
	sf::RenderWindow& getWindow(){ return window; };
private:
	sf::RenderWindow &window;
	sf::Color clear_color;

};

