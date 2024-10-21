#include "GameObjectFactory.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GraphicsSystem.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "TextComponent.h"
#include "CollisionComponent.h"

GameObjectFactory::GameObjectFactory()
{
}


GameObjectFactory::~GameObjectFactory()
{
}

int GameObjectFactory::GreateStaticObject(SystemManager &_manager, std::string _texture, int _gsystem, sf::Vector2f _pos, sf::Vector2f _size)
{
	GameObject ob;
	ob.AddComponent(new RenderComponent);

	//Add the values to component
	if (_manager.GetSystem(_gsystem) != nullptr)
	{
		GraphicsSys(_manager, _gsystem)->LoadTexture(ob,_texture);
		GraphicsSys(_manager, _gsystem)->AddShape(ob, _pos, _size, sf::Vector2f(RendComponent(ob)->texture.getSize()));
	}
	
	int id = _manager.RegisterGameObject(ob);
	return id;
}

int GameObjectFactory::GreateObject(SystemManager &_manager, std::string _texture, int _gsystem, sf::Vector2f _pos, sf::Vector2f _size)
{
	GameObject ob;
	ob.AddComponent(new RenderComponent);
	ob.AddComponent(new TransformComponent);

	TransComponent(ob)->size = _size;
	TransComponent(ob)->position = _pos;

	//Add the values to component
	if (_manager.GetSystem(_gsystem) != nullptr)
	{
		GraphicsSys(_manager, _gsystem)->LoadTexture(ob, _texture);
		GraphicsSys(_manager, _gsystem)->AddShape(ob);
	}

	int id = _manager.RegisterGameObject(ob);
	return id;
}

int GameObjectFactory::GreatePhysicsObject(SystemManager &_manager, int _psystem, b2Vec2 _pos)
{
	GameObject ob;
	ob.AddComponent(new PhysicsComponent);

	//Set body defintions
	b2BodyDef pdef;
	pdef.position.Set(_pos.x / PMETER, _pos.y / PMETER);

	//Add the values to component
	if (_manager.GetSystem(_psystem) != nullptr)
	{
		PhysComponent(ob)->body = PhysicsSys(_manager, _psystem)->getWorld().CreateBody(&pdef);
	}

	int id = _manager.RegisterGameObject(ob);
	return id;
}

int GameObjectFactory::GreateTextObject(SystemManager &_manager, std::string _font, int _gsystem, sf::Vector2f _pos, int _size, sf::Color _color)
{
	GameObject ob;
	ob.AddComponent(new TextComponent);

	FontComponent(ob)->text.setCharacterSize(_size);
	FontComponent(ob)->text.setPosition(_pos);
	FontComponent(ob)->text.setColor(_color);

	//Add the values to component
	if (_manager.GetSystem(_gsystem) != nullptr)
	{
		GraphicsSys(_manager, _gsystem)->LoadFont(ob,_font);
	}

	int id = _manager.RegisterGameObject(ob);
	return id;
}


void GameObjectFactory::AddPhysics(GameObject& _ob, b2World& _world, bool _fixture, bool _circle, bool _dynamic)
{
	_ob.AddComponent(new PhysicsComponent);

	if (_ob.getComponent(Comp::TRANS) != nullptr)
	{
		b2BodyDef pdef;
		//Set body defintions

		//If _dynamic = true sets body type to dynamic (else its static)
		if (_dynamic == true)
			pdef.type = b2_dynamicBody;

		pdef.position.Set(TransComponent(_ob)->position.x / PMETER, TransComponent(_ob)->position.y / PMETER);

		//Set initial fixture
		b2FixtureDef fixtureDef;

		//Set shape definitions
		b2PolygonShape shape;
		b2CircleShape circle;

		//Add the values to component
		PhysComponent(_ob)->body =  _world.CreateBody(&pdef);

		//Add fixture that has same size as object transform
		if (_fixture == true)
		{
			if (_circle == false)
			{
				shape.SetAsBox((TransComponent(_ob)->size.x*0.47f) / PMETER, (TransComponent(_ob)->size.y*0.47f) / PMETER);
				fixtureDef.shape = &shape;
			}
			else
			{
				circle.m_p.Set(0, 0);
				circle.m_radius = TransComponent(_ob)->size.x*0.47f / PMETER;
				fixtureDef.shape = &circle;
			}

			// Define the dynamic body fixture.
			if (_dynamic == true)
				fixtureDef.density = 4.0f;

			//Add fixture to body
			PhysComponent(_ob)->body->CreateFixture(&fixtureDef);
		}
	}
}

void GameObjectFactory::AddFixture(GameObject& _ob, b2Vec2& _pos, b2Vec2  _size, bool _circle, float _angle, bool _dynamic)
{
	if (_ob.getComponent(Comp::PHYS))
	{
		b2FixtureDef fixtureDef;

		//Set shape definitions
		b2PolygonShape shape;
		b2CircleShape circle;

		
	
		if (_circle == false)
		{
			shape.SetAsBox(_size.x*0.47f / PMETER, _size.y*0.47f / PMETER, b2Vec2(_pos.x / PMETER, _pos.y / PMETER), _angle);
			fixtureDef.shape = &shape;
		}
		else
		{
			circle.m_p.Set(0, 0);
			circle.m_radius = TransComponent(_ob)->size.x*0.47f / PMETER;
			fixtureDef.shape = &circle;
		}


		// Define the dynamic body fixture.
		if (_dynamic == true)
			fixtureDef.density = 1.0f;

		PhysComponent(_ob)->body->CreateFixture(&fixtureDef);
	}
}

void GameObjectFactory::ChangePhysicValues(GameObject& _ob, float _density, float _friction, float _restitution)
{
	if (_ob.getComponent(Comp::PHYS) != nullptr)
	{
		for (b2Fixture* f = PhysComponent(_ob)->body->GetFixtureList(); f; f = f->GetNext())
		{
			f->SetDensity(_density);
			f->SetFriction(_friction);
			f->SetRestitution(_restitution);
		}
		PhysComponent(_ob)->body->ResetMassData();
	}
}

void GameObjectFactory::AddInput(GameObject& _ob, std::vector<int> _inp)
{
	_ob.AddComponent(new InputComponent);
	InpComponent(_ob)->input = _inp;
}

void GameObjectFactory::AddCollision(GameObject& _ob, bool _auto, sf::Vector2f _size, sf::Vector2f _offset)
{
	_ob.AddComponent(new CollisionComponent);
	if (_ob.getComponent(Comp::TRANS) != nullptr && _ob.getComponent(Comp::TRANS) == nullptr)//Needs  to be updated somewhere
	{
		if (_auto == true)
		{
			CollComponent(_ob)->Area = sf::Rect<float>(TransComponent(_ob)->position, TransComponent(_ob)->size);
		}
		else
		{
			CollComponent(_ob)->Area = sf::Rect<float>(TransComponent(_ob)->position+_offset, _size);
		}
	}

	if (_ob.getComponent(Comp::PHYS) != nullptr)
	{
		if (_auto == true)
		{
			CollComponent(_ob)->Area = sf::Rect<float>(sf::Vector2f(PhysComponent(_ob)->body->GetPosition().x * 100 - TransComponent(_ob)->size.x*0.5f,
				PhysComponent(_ob)->body->GetPosition().y * 100 - TransComponent(_ob)->size.y*0.5f), TransComponent(_ob)->size);
		}
		else
		{
			CollComponent(_ob)->Area = sf::Rect<float>(sf::Vector2f(PhysComponent(_ob)->body->GetPosition().x * 100 - TransComponent(_ob)->size.x*0.5f,
				PhysComponent(_ob)->body->GetPosition().y * 100 - TransComponent(_ob)->size.y*0.5f) + _offset, _size);
		}
	}
}