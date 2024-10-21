#pragma once
#include <Box2D\Box2D.h>
#include <System.h>


#define PhysicsSys(x, i) dynamic_cast<PhysicsSystem*>(x.GetSystem(i))

static const float PMETER = 100.0f;//amount of pixels in a meter

class PhysicsSystem : public System
{
public:
	PhysicsSystem(b2Vec2 _gravity);
	~PhysicsSystem();
	void Update(GameObject& _object);

	b2World& getWorld(){ return world; }

private:
	
	b2Vec2 gravity;// Define the gravity vector.
	b2World world;// Construct a world object, which will hold and simulate the rigid bodies.
	b2BodyDef groundBodyDef;// Define the ground body.

	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;

};
