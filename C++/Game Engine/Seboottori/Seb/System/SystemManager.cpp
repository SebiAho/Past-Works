#include "SystemManager.h"

#include <iostream>

using namespace seb;

SystemManager::SystemManager() :running(true)
{

}


SystemManager::~SystemManager()
{
}

int SystemManager::AddSystem(System* _system)
{
	int index = -1;
	//std::map<seb::SYS, unsigned int>::iterator it;
	if ((SYS)_system->getId() == SYS::DEFAULT)//Check if system has type
		return index;

	if (_system->getId() & system_id_sum)//Check if _system.id matches the id of another system, if match returns from function
		return index;

	if ((system_id_sum & (unsigned int)SYS::GRAPHICS))//Check if graphics system is in system_array and if true makes sure it's last in system_array
	{
		//Relocate grapics system to temp variable
		System* temp_g = system_array.back();
		system_array.pop_back();

		//Add system to the array
		system_array.push_back(_system);
		index = system_array.size() - 1;
		sys_index_map.insert(std::pair<SYS, int>((SYS)_system->getId(), index));
		system_id_sum += _system->getId();//Add system id to added_systems variable

		//Add grapics system pack to system_array
		system_array.push_back(temp_g);
		sys_index_map[SYS::GRAPHICS] = index + 1;//change grapichs system index to match new position

		return index;
	}
	else//Add system to system_array
	{
		system_array.push_back(_system);
		index = system_array.size() - 1;
		sys_index_map.insert(std::pair<SYS, int>((SYS)_system->getId(), index));
		system_id_sum += _system->getId();
		return index;
	}


}

int SystemManager::RemoveSystem()
{
	return 0;
}

void SystemManager::Initialize()
{
	for (unsigned int i = 0; i < system_array.size(); i++)
	{
		system_array.at(i)->Intitialize(objects);
	}
}

void SystemManager::Update()
{
	DistributeMessages();
	for (unsigned int i = 0; i < system_array.size(); i++)
	{
		system_array.at(i)->Update();
	}
}

System* SystemManager::getSystem(SYS _sys)
{
	try
	{
		if ((unsigned int)_sys & system_id_sum)
			return system_array.at(sys_index_map[_sys]);
		else
			throw -1;
	}
	catch (int e)
	{
		std::cout << e << "Could not find system of type " << (unsigned int)_sys << std::endl;
	}
}

void SystemManager::DistributeMessages()
{
	while (messages.UnhandledMessages() == true)
	{
		for (unsigned int i = 0; i < system_array.size(); i++)//Distripute messages across systems
		{
			system_array.at(i)->handleMessage(messages);
		}
		messages.DiscardMessage(system_id_sum);//Discard SYS::ALL messages and messages lacking valid systemID
	}
}