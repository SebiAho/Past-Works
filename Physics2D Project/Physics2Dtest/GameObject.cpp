#include "GameObject.h"
#include <cassert>

GameObject::GameObject() :id(-1), in_use(false)
{
}


GameObject::~GameObject()
{

}

Component* GameObject::getComponent(Comp _id)
{
	std::map<Comp, Component*>::iterator it;
	if ((it = o_components.find(_id)) != o_components.end())
	{
		return it->second;
	}
	return nullptr;
}

void GameObject::AddComponent(Component *_comp)
{
	o_components.insert(std::pair<Comp, Component*>(_comp->getId(), _comp));
}

void GameObject::RemoveComponent(Comp _id)
{
	std::map<Comp, Component*>::iterator it;
	if ((it = o_components.find(_id)) != o_components.end())
	{
		delete it->second;
		o_components.erase(_id);
	}
}