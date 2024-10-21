#pragma once
#include "Component.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

//Component redefinitions
#define RendComponent(x) dynamic_cast<RenderComponent*>(x.getComponent(Comp::REND))

class RenderComponent: public Component
{
public:
	RenderComponent();
	~RenderComponent();

	sf::Texture texture;
	sf::VertexArray shape;
	sf::RenderStates state;//Contains texture and images transform data
};

