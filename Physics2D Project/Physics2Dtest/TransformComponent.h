#pragma once
#include "Component.h"
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Transformable.hpp>

#define TransComponent(x) dynamic_cast<TransformComponent*>(x.getComponent(Comp::TRANS))

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	sf::Vector2f position, size;
	sf::Transformable transform;
};

