#include "Program.h"

#include "GameObjectFactory.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "CollisionComponent.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <Windows.h>

Program::Program() :window_size(800, 600), force(0.0f), attempts(0), level(1), in_basket(false)
{
}


Program::~Program()
{
}

void Program::Loop()
{
	bool exit = false;
	sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Window");
	sf::Event event;

	//Systems
	SystemManager manager;
	int physicsId = manager.AddSubSystem(new PhysicsSystem(b2Vec2(0.0f, 0.0)));
	int inputId = manager.AddSubSystem(new InputSystem(window));
	int graphicsId = manager.AddSubSystem(new GraphicsSystem(window));

	InitializeLevel(0, manager, graphicsId, physicsId);

	InitializeLevel(1, manager, graphicsId, physicsId);
	while (!exit)
	{
		// check window's events
		
		while (window.pollEvent(event))
		{
			manager.HandleMessages(event);

			if (event.type == sf::Event::MouseButtonPressed /*&& PhysComponent(manager.getObject(Ball))->body->GetLinearVelocity().y < 2.0f && PhysComponent(manager.getObject(Ball))->body->GetLinearVelocity().x < 2.0f*/)
			{
				manager.getObject(4).setOn(true);
				PhysComponent(manager.getObject(4))->body->SetActive(true);
				PhysComponent(manager.getObject(4))->body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
				PhysComponent(manager.getObject(4))->body->SetTransform(b2Vec2((TransComponent(manager.getObject(2))->position.x-20)/100, (TransComponent(manager.getObject(2))->position.y+16)/100), 0);
				PhysComponent(manager.getObject(4))->body->ApplyLinearImpulse(b2Vec2(cos(InputSys(manager, inputId)->getAngle()) * force,	sin(InputSys(manager, inputId)->getAngle()) * force),
					PhysComponent(manager.getObject(4))->body->GetWorldCenter(), true);
				attempts++;
			}
		}
		//Detect if ball is in basket
		if (manager.getObject(4).getOn() == true && CollComponent(manager.getObject(7))->Area.intersects(CollComponent(manager.getObject(4))->Area))
		{
			in_basket = true;
		}

		//Change level
		if (in_basket == true && level < 4)
		{
			Sleep(1000);
			level++;
			InitializeLevel(level, manager, graphicsId, physicsId);
			in_basket = false;
		}

		manager.Update();
		UpdateText(manager, graphicsId, InputSys(manager, inputId)->getAngle(), PhysicsSys(manager, physicsId)->getWorld().GetGravity().y);

		//Draw
		GraphicsSys(manager, graphicsId)->BeginDraw();

		DrawLevel(manager, graphicsId);

		GraphicsSys(manager, graphicsId)->EndDraw();
		
	}

	
}

void Program::InitializeLevel(int _level, SystemManager& _manager, int _rendId, int _physId)
{
	int temp_id;
	std::stringstream a;

	switch (_level)
	{
	case 0://Initial initilization
		object_amount = 0;
		text_amount = 0;
		//Background object (0)
		temp_id = GameObjectFactory::GreateStaticObject(_manager, "Background.png", _rendId, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 600.0f));
		object_amount++;

		//Wall collision object (1)
		temp_id = GameObjectFactory::GreatePhysicsObject(_manager, _physId, b2Vec2(0.0f, 0.0f));
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(400.0f, 600.0f), b2Vec2(800.0f, 1.0f));//Ground
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(0.0f, 300.0f), b2Vec2(1.0f, 600.0f));//Left wall
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(800.0f, 300.0f), b2Vec2(1.0f, 600.0f));//Right wall
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(400.0f, 0.0f), b2Vec2(800.0f, 1.0f));//Ceiling
		object_amount++;

		//Arrow (2)
		temp_id = GameObjectFactory::GreateObject(_manager, "Arrow.png", _rendId, sf::Vector2f(55.0f, 300.0f), sf::Vector2f(64.0f, 32.0f));
		GameObjectFactory::AddInput(_manager.getObject(temp_id), { 1, 2 });
		object_amount++;

		//Shelf (3)
		temp_id = GameObjectFactory::GreateObject(_manager, "Shelf.png", _rendId, sf::Vector2f(44.0f, 300.0f), sf::Vector2f(32.0f, 64.0f));
		GameObjectFactory::AddInput(_manager.getObject(temp_id), { 1 });
		object_amount++;

		//Ball (4)
		temp_id = GameObjectFactory::GreateObject(_manager, "Ball.png", _rendId, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(64.0f, 64.0f));//Initial transform position doesnt matter
		GameObjectFactory::AddPhysics(_manager.getObject(temp_id), PhysicsSys(_manager, _physId)->getWorld(), true, true,true);
		GameObjectFactory::ChangePhysicValues(_manager.getObject(temp_id), 3, 1, 0.2f);
		GameObjectFactory::AddCollision(_manager.getObject(temp_id), false, sf::Vector2f(30.0f, 30.0f));
		PhysComponent(_manager.getObject(temp_id))->body->SetActive(false);
		_manager.getObject(temp_id).setOn(false);
		object_amount++;

		//Ball 2 (5)
		temp_id = GameObjectFactory::GreateObject(_manager, "Ball.png", _rendId, sf::Vector2f(205.0f, 600.0f), sf::Vector2f(64.0f, 64.0f));//Initial transform position doesnt matter
		GameObjectFactory::AddPhysics(_manager.getObject(temp_id), PhysicsSys(_manager, _physId)->getWorld(), true, true);
		PhysComponent(_manager.getObject(temp_id))->body->SetActive(false);//Should be made so physics are diasbeld automatically if object is set off
		_manager.getObject(temp_id).setOn(false);
		object_amount++;

		//Ball 3 (6)
		temp_id = GameObjectFactory::GreateObject(_manager, "Ball.png", _rendId, sf::Vector2f(205.0f, 600.0f), sf::Vector2f(64.0f, 64.0f));//Initial transform position doesnt matter
		GameObjectFactory::AddPhysics(_manager.getObject(temp_id), PhysicsSys(_manager, _physId)->getWorld(), true, true);
		PhysComponent(_manager.getObject(temp_id))->body->SetActive(false);//Should be made so physics are diasbeld automatically if object is set off
		_manager.getObject(temp_id).setOn(false);
		object_amount++;

		//Basket (7)
		temp_id = GameObjectFactory::GreateObject(_manager, "Basket.png", _rendId, sf::Vector2f(450.0f, 515.0f), sf::Vector2f(102.4f, 51.2f));
		GameObjectFactory::AddPhysics(_manager.getObject(temp_id), PhysicsSys(_manager, _physId)->getWorld(), false, false, false);
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(0.0f, 22.0f), b2Vec2(80.0f, 0.01f));//Bottom collision
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(-42.0f, 0.0f), b2Vec2(51.2f, 0.01f), false, 68 * 3.14159265f / 180);//Left side
		GameObjectFactory::AddFixture(_manager.getObject(temp_id), b2Vec2(42.0f, 0.0f), b2Vec2(51.2f, 0.01f), false, -68 * 3.14159265f / 180);//Right side
		GameObjectFactory::AddCollision(_manager.getObject(temp_id), false, sf::Vector2f(50.0f, 10.0f));
		object_amount++;

		//Shelf position text (8)
		temp_id = GameObjectFactory::GreateTextObject(_manager, "RujisHandwritingFontv.2.0.otf", _rendId, sf::Vector2f(20.0f, 0.0f), 14, sf::Color::White);
		text_amount++;

		//Angle text (9)
		temp_id = GameObjectFactory::GreateTextObject(_manager, "RujisHandwritingFontv.2.0.otf", _rendId, sf::Vector2f(250.0f, 0.0f), 14, sf::Color::White);
		text_amount++;

		//Gravity, force and basket position text(10)
		temp_id = GameObjectFactory::GreateTextObject(_manager, "RujisHandwritingFontv.2.0.otf", _rendId, sf::Vector2f(360.0f, 0.0f), 14, sf::Color::White);
		text_amount++;

		//Attempts(11)
		temp_id = GameObjectFactory::GreateTextObject(_manager, "RujisHandwritingFontv.2.0.otf", _rendId, sf::Vector2f(20.0f, 580.0f), 14, sf::Color::White);
		text_amount++;

		break;
	case 1:
		attempts = 0;

		//Reset ball
		_manager.getObject(4).setOn(false);
		PhysComponent(_manager.getObject(4))->body->SetActive(false);
		
		//Set force, grafity and basket position
		PhysicsSys(_manager, _physId)->getWorld().SetGravity(b2Vec2(0.0f, 9.81f));
		force = 5.0f;
		PhysComponent(_manager.getObject(7))->body->SetTransform(b2Vec2(700.0f / 100, 550.0f / 100), 0);

		//Set constant text values
		a.str(std::string());
		a << std::fixed << std::setprecision(2) << "G: " << PhysicsSys(_manager, _physId)->getWorld().GetGravity().y
			<< "  F: " << force << "  Mass: " << PhysComponent(_manager.getObject(4))->body->GetMass() << "kg" <<
			"  Basket pos:  x " << PhysComponent(_manager.getObject(7))->body->GetPosition().x << "m  y  " << PhysComponent(_manager.getObject(7))->body->GetPosition().y << "m";

		FontComponent(_manager.getObject(object_amount + 2))->content = a.str();
		GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount + 2));
		break;

	case 2:
		attempts = 0;

		//Reset ball
		_manager.getObject(4).setOn(false);
		PhysComponent(_manager.getObject(4))->body->SetActive(false);

		//Set force, grafity and basket position
		PhysicsSys(_manager, _physId)->getWorld().SetGravity(b2Vec2(0.0f, 4.9f));
		force = 10.0f;
		PhysComponent(_manager.getObject(7))->body->SetTransform(b2Vec2(500.0f / 100, 150.0f / 100), 0);

		//Set constant text values
		a.str(std::string());
		a << std::fixed << std::setprecision(2) << "G: " << PhysicsSys(_manager, _physId)->getWorld().GetGravity().y
			<< "  F: " << force << "  Mass: " << PhysComponent(_manager.getObject(4))->body->GetMass() << "kg" <<
			"  Basket pos:  x " << PhysComponent(_manager.getObject(7))->body->GetPosition().x << "m  y  " << PhysComponent(_manager.getObject(7))->body->GetPosition().y << "m";

		FontComponent(_manager.getObject(object_amount + 2))->content = a.str();
		GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount + 2));
		break;

	case 3:
		attempts = 0;

		//Reset ball
		_manager.getObject(4).setOn(false);
		PhysComponent(_manager.getObject(4))->body->SetActive(false);

		//Set force, grafity and basket position
		PhysicsSys(_manager, _physId)->getWorld().SetGravity(b2Vec2(0.0f, 0.0f));
		force = 10.0f;
		PhysComponent(_manager.getObject(7))->body->SetTransform(b2Vec2(480.0f / 100, 150.0f / 100), 0);

		//Set Ball 2 active
		PhysComponent(_manager.getObject(5))->body->SetTransform(b2Vec2(320.0f / 100, 100.0f / 100), 0);
		_manager.getObject(5).setOn(true);
		PhysComponent(_manager.getObject(5))->body->SetActive(true);


		//Set constant text values
		a.str(std::string());
		a << std::fixed << std::setprecision(2) << "G: " << PhysicsSys(_manager, _physId)->getWorld().GetGravity().y
			<< "  F: " << force << "  Mass: " << PhysComponent(_manager.getObject(4))->body->GetMass() << "kg" <<
			"  Basket pos:  x " << PhysComponent(_manager.getObject(7))->body->GetPosition().x << "m  y  " << PhysComponent(_manager.getObject(7))->body->GetPosition().y << "m";

		FontComponent(_manager.getObject(object_amount + 2))->content = a.str();
		GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount + 2));
		break;

	case 4:
		attempts = 0;
		
		_manager.getObject(4).setOn(false);
		PhysComponent(_manager.getObject(4))->body->SetActive(false);

		PhysicsSys(_manager, _physId)->getWorld().SetGravity(b2Vec2(0.0f, 0.0f));
		force = 10.0f;
		PhysComponent(_manager.getObject(7))->body->SetTransform(b2Vec2(200.0f / 100, 570.0f / 100), 0);

		PhysComponent(_manager.getObject(5))->body->SetTransform(b2Vec2(350.0f / 100, 270.0f / 100), 0);
		GameObjectFactory::ChangePhysicValues(_manager.getObject(5), 2, 0, 1.0f);
		_manager.getObject(5).setOn(true);
		PhysComponent(_manager.getObject(5))->body->SetActive(true);

		//Set ball 6 active
		PhysComponent(_manager.getObject(6))->body->SetTransform(b2Vec2(350.0f / 100, 350.0f / 100), 0);
		GameObjectFactory::ChangePhysicValues(_manager.getObject(6), 2, 0, 1.0f);
		_manager.getObject(6).setOn(true);
		PhysComponent(_manager.getObject(6))->body->SetActive(true);

		//Set constant text values
		a.str(std::string());
		a << std::fixed << std::setprecision(2) << "G: " << PhysicsSys(_manager, _physId)->getWorld().GetGravity().y
			<< "  F: " << force << "  Mass: " << PhysComponent(_manager.getObject(4))->body->GetMass() << "kg" <<
			"  Basket pos:  x " << PhysComponent(_manager.getObject(7))->body->GetPosition().x << "m  y  " << PhysComponent(_manager.getObject(7))->body->GetPosition().y << "m";

		FontComponent(_manager.getObject(object_amount + 2))->content = a.str();
		GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount + 2));
		break;
	}

}

void Program::UpdateText(SystemManager& _manager, int _rendId, float _angle, float _gravity)
{
	std::stringstream a;

	//Ball starting position
	a << std::fixed << std::setprecision(2) << "Start pos:  x " << (TransComponent(_manager.getObject(2))->position.x - 20) / 100 << "m  y "//Convert to 2 decimal point numbers
		<< (TransComponent(_manager.getObject(2))->position.y - 17) / 100 << "m";

	FontComponent(_manager.getObject(object_amount+0))->content = a.str();
	GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount));

	//Launch angle
	a.str(std::string());//Clear stream
	a << std::fixed << std::setprecision(2) << "Angle: " << (_angle * 180 / 3.14159265f)*-1<<"°";

	FontComponent(_manager.getObject(object_amount+1))->content = a.str();
	GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount + 1));

	//Attempts
	a.str(std::string());//Clear stream
	a << "Level " << level << "  Attempts: " << attempts;

	FontComponent(_manager.getObject(object_amount + 3))->content = a.str();
	GraphicsSys(_manager, _rendId)->SetText(_manager.getObject(object_amount + 3));
}

void Program::DrawLevel(SystemManager& _manager, int _rendId)
{
	//Draw background
	GraphicsSys(_manager, _rendId)->StaticDraw(_manager.getObject(0));

	//Draw objects
	for (int i = 1; i < object_amount; ++i)
	{
		GraphicsSys(_manager, _rendId)->Draw(_manager.getObject(i));
	}

	//Draw text
	for (int i = object_amount; i < text_amount+object_amount; ++i)
	{
		GraphicsSys(_manager, _rendId)->DrawGameText(_manager.getObject(i));
	}
}

