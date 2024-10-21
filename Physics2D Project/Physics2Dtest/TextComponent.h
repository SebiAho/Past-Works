#pragma once
#include "Component.h"

#include <SFML\Graphics\Text.hpp>
#include <string>

//Component redefinitions
#define FontComponent(x) dynamic_cast<TextComponent*>(x.getComponent(Comp::TEXT))

class TextComponent : public Component
{
public:
	TextComponent();
	~TextComponent();

	std::string content;
	sf::Font font;
	sf::Text text;
};

