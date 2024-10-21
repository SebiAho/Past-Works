#pragma once
#include "Component.h"
#include <SFML\Graphics\Rect.hpp>

//Component redefinitions
#define CollComponent(x) dynamic_cast<CollisionComponent*>(x.getComponent(Comp::COLL))

class CollisionComponent : public Component
{
public:
	CollisionComponent();
	~CollisionComponent();

	sf::Rect<float> Area;
};

