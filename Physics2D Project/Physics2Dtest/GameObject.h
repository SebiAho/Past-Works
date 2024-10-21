#pragma once

#include <map>
#include "Component.h"



class GameObject
{
public:
	GameObject();
	~GameObject();
	Component* getComponent(Comp _id);

	void AddComponent(Component *_comp);

	void RemoveComponent(Comp _id);

	//Getters & Setters
	bool getOn(){ return in_use; };
	void setOn(bool _status){ in_use = _status; };
	
	int getId(){ return id; };
	void setId(int _id){ id = _id; };

private:
	std::map<Comp, Component*> o_components;
	bool in_use;//Used to set the gameobject on/off
	int id;//A simple numper of objects location in a game object list (Setting it to some other than -1 prevents objects inclusion to a list)
};

