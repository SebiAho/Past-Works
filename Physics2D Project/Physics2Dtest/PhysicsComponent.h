#pragma once
#include "Component.h"
#include <Box2D\Box2D.h>

//Component redefinitions
#define PhysComponent(x) dynamic_cast<PhysicsComponent*>(x.getComponent(Comp::PHYS))

class PhysicsComponent: public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	b2Body *body;
};

