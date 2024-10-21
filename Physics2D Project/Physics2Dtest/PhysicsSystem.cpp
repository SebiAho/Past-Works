#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"

PhysicsSystem::PhysicsSystem(b2Vec2 _gravity) : System(Sys::PHYSICS), gravity(_gravity), world(b2World(_gravity))
{
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update(GameObject& _object)
{
	if (use == true)
	{
		// Instruct the world to perform a single step of simulation.
		world.Step(timeStep, velocityIterations, positionIterations);

		use = false;
	}

	if (_object.getComponent(Comp::PHYS) != nullptr)
	{
		if (_object.getComponent(Comp::TRANS) != nullptr)
		{
			
			//Convert the physics transform values to transfrom component values
			TransComponent(_object)->position.x = (PhysComponent(_object)->body->GetPosition().x * PMETER)- TransComponent(_object)->size.x/2;
			TransComponent(_object)->position.y = (PhysComponent(_object)->body->GetPosition().y * PMETER)- TransComponent(_object)->size.y / 2;
			
			if (_object.getComponent(Comp::COLL) != nullptr)
			{
				CollComponent(_object)->Area.left = PhysComponent(_object)->body->GetPosition().x * 100 - TransComponent(_object)->size.x*0.5f;
				CollComponent(_object)->Area.top = PhysComponent(_object)->body->GetPosition().y * 100 - TransComponent(_object)->size.y*0.5f;
			}
		}

	}
}
