#include "SystemManager.h"


SystemManager::SystemManager()
{
}


SystemManager::~SystemManager()
{
}

void SystemManager::Inititalize()
{
}

void SystemManager::Update()
{
	for (int x = 0; x < objects.size(); ++x)
	{
		if (objects.at(x).getOn() == true)//Check is object in use
		{
			for (int y = 0; y < SubSystems.size(); ++y)
			{
				SubSystems.at(y)->Update(objects.at(x));
			}
		}
	}

	//Reset use variables
	for (int i = 0; i < SubSystems.size(); ++i)
	{
		SubSystems.at(i)->resetUse();
	}
}

void SystemManager::HandleMessages(sf::Event _event)
{
	for (int i = 0; i < SubSystems.size(); ++i)
	{
		SubSystems.at(i)->HandleMessages(_event);
	}
}

int SystemManager::AddSubSystem(System* _system)
{
	bool included = false;
	int location = 0;//Systems locations in SubSystmes
	for (int i = 0; i < SubSystems.size(); ++i)
	{
		if (SubSystems.at(i)->getId() == _system->getId())
		{
			included = true;
			break;
		}
		location = i +1;
	}

	if (!included)
	{
		SubSystems.push_back(_system);
		return location;
	}
	
	return -1;
}

int SystemManager::RemoveSubSystem(int _loc)
{
	if (objects.size() < _loc + 1)
	{
		objects.erase(objects.begin() + _loc);
		return -1;
	}
	return _loc;
}

int SystemManager::RegisterGameObject(GameObject& _object)
{
	int location = -1;
	if (_object.getId() == -1)
	{
		location = objects.size();
		objects.push_back(_object);
		objects.at(location).setId(location);
		objects.at(location).setOn(true);
		return location;//Return id of registered object
	}
	return location;
}

int SystemManager::UnregisterGameObject(int _id)
{
	if (objects.size() < _id +1)
	{
		objects.erase(objects.begin()+_id);
		return -1;
	}
	return _id;
}

void SystemManager::ToggleObject(int _id, bool _value)
{
	objects.at(_id).setOn(_value);
}