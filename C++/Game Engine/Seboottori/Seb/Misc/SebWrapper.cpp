#include "SebWrapper.h"

using namespace seb;

Seb_Wrapper::Seb_Wrapper()
{
}


Seb_Wrapper::~Seb_Wrapper()
{
}

void Seb_Wrapper::SetupSystems(SystemManager& _systems, bool _network)
{
	systems = &_systems;

	_systems.AddSystem(new seb::GraphicsSystem);
	_systems.AddSystem(new seb::InputSystem);
	if (_network)
	{
		//add network system
	}
}

GraphicsSystem* Seb_Wrapper::GetGraphic()
{
	return static_cast<GraphicsSystem*>(systems->getSystem(SYS::GRAPHICS));
}

InputSystem* Seb_Wrapper::GetInput()
{
	return static_cast<InputSystem*>(systems->getSystem(SYS::INPUT));
}
