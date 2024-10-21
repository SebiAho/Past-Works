#include "Object.h"

#include <iostream>

using namespace seb;

Object::Object() :comp_type_sum(0), On(true)
{
}


Object::~Object()
{
}

Component* Object::getComponent(COMP _type)
{
	try
	{
		if ((unsigned int)_type & comp_type_sum)
			return components[_type];
		else
			throw - 1;
	}
	catch (int e)
	{
		std::cout << e << "Could not find component of type " << (unsigned int)_type << " in object index " << id.index << " refision " << id.revision << std::endl;
	}
}

int Object::AddComponent(Component &_component)
{
	//Check that component isn't already included in the object 
	if (comp_type_sum & (unsigned int)_component.getType())
		return -1;

	//Add pointer of component to object
	components.insert(std::pair<COMP,Component*>((COMP)_component.getType(), &_component));
	comp_type_sum += (unsigned int)_component.getType();

	return components.size()-1;
}

int Object::RemoveComponent(Component& _component)
{
	//Check that component is included in the object 
	if (!(comp_type_sum & (unsigned int)_component.getType()))
		return -1;

	//Remove object
	std::map<COMP, Component*>::iterator it = components.find(_component.getType());
	components.erase(it);
	comp_type_sum -= (unsigned int)_component.getType();
	return _component.getId().index;
}

void Object::Copy(const Object &_object)
{
	id = _object.id;
	On = _object.On;
	components = _object.components;
	comp_type_sum = _object.comp_type_sum;


}