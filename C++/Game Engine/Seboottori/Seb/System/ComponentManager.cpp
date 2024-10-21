#include "ComponentManager.h"
#include <iostream>

using namespace seb;

//Component Manager
ComponentManager::ComponentManager() :comp_type_sum(0)
{
}

ComponentManager::~ComponentManager()
{
}

int ComponentManager::addHandler(COMP _type)
{
	if (!((unsigned int)_type & comp_type_sum))
	{
		ComponentHandler h;
		h.type = _type;
		handler_map.insert(std::pair<COMP, ComponentHandler>(_type, h));
		comp_type_sum += (unsigned int)_type;

		return (int)_type;
	}
	return -1;
}

int ComponentManager::removeHandler(COMP _type)
{
	if ((unsigned int)_type & comp_type_sum)
	{
		std::unordered_map<COMP, ComponentHandler>::iterator it = handler_map.find(_type);
		handler_map.erase(it);
		comp_type_sum -= (unsigned int)_type;

		return (int)_type;
	}
	return -1;
}

void  ComponentManager::UseHandler(COMP _type, bool _use)
{
	//Check that handler type is included in manager 
	if ((unsigned int)_type & comp_type_sum)
	{
		if (_use == true)
			handler_map[_type].inUse = false;
		else
			handler_map[_type].inUse = true;
	}
}

ComponentHandler& ComponentManager::getHandler(COMP _type)
{
	try
	{
		if ((unsigned int)_type & comp_type_sum)
			return handler_map[_type];
		else
			throw - 1;
	}
	catch (int e)
	{
		std::cout << e <<" Handler of type "<< (unsigned int)_type << " not found" << std::endl;
	}
}

