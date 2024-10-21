#pragma once
#include "SystemManager.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <string>
#include <Box2D\Dynamics\b2World.h>

class GameObjectFactory//Contains functions that help in GameObject creation
{
public:
	~GameObjectFactory();

	
	static int GreateStaticObject(SystemManager &_manager, std::string _texture, int _gsystem, sf::Vector2f _pos, sf::Vector2f _size);//Stationary object that only posesses a render component 
	static int GreateObject(SystemManager &_manager, std::string _texture, int _gsystem, sf::Vector2f _pos, sf::Vector2f _size);//Basic object that has both render and transform components
	static int GreatePhysicsObject(SystemManager &_manager, int _psystem, b2Vec2 _pos);//Base object with only physics component
	static int GreateTextObject(SystemManager &_manager, std::string _font, int _gsystem, sf::Vector2f _pos, int _size, sf::Color _color);//Objects used to diasplay game text

	static void AddPhysics(GameObject& _ob, b2World& _world, bool _fixture = true, bool _circle = false, bool _dynamic = true);//Add physic component and set starting values to a GameObject with transfromcomponent
	static void AddFixture(GameObject& _ob, b2Vec2& _pos, b2Vec2  _size, bool _circle = false, float _angle = 0, bool _dynamic = true);//Adds a adittional fixture to object (Allows creation of more complicated physic shapes)
	static void ChangePhysicValues(GameObject& _ob, float _density, float _friction, float _restitution);
		
	static void AddInput(GameObject& _ob, std::vector<int> _inp);//Adds inputComponent to a GameObject and sets input input keys
	static void AddCollision(GameObject& _ob, bool _auto = true, sf::Vector2f _size = sf::Vector2f(0.0f, 0.0f), sf::Vector2f _offset = sf::Vector2f(0.0f, 0.0f));//Adds collision component to the object and calculates its location

private:
	GameObjectFactory();
};

