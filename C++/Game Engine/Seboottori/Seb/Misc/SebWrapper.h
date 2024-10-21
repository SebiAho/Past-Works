#pragma once
#include "..\System\SystemManager.h"
#include "..\Graphics\GraphicsSystem.h"
#include "..\Input\InputSystem.h"

namespace seb
{
	class Seb_Wrapper//Wrapper class for Seb engine that simplifies it's use
	{
	public:
		Seb_Wrapper();
		~Seb_Wrapper();

		/*Prepares SystemManager with graphics and input systems + opitional systems, _systems = reference to system manager,bool ... = optional systems*/
		void SetupSystems(SystemManager& _systems, bool _network = false);

		//System casts
		GraphicsSystem* GetGraphic();
		InputSystem*GetInput();

	private:
		SystemManager* systems;
	};
}
