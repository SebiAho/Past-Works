#include "ObjectManager.h"
#include <iostream>

using namespace seb;
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

ObjectID ObjectManager::AddObject(Object& _object)
{
	ObjectID id;
	id.index = -1;
	id.revision = counter;

	//Check if unused objects array is empty
	if (removed_objects.empty() == true)
	{
		//Assign object to a new slot in object_array
		object_array.push_back(new Object(_object));
		id.index = object_array.size() - 1;
		object_array.back()->setID(id);
		return id;
	}
	else
	{
		//Assign object to an unused slot in object_array
		id.index = removed_objects.back();
		_object.setID(id);
		object_array.at(id.index)->Copy(_object);
		removed_objects.pop_back();//Might be possiple to replace at some point
		return id;
	}
}

int ObjectManager::ToggleObject(ObjectID _id, bool _on)
{
	if (_id.revision == object_array[_id.index]->getID().revision)//Check if refision of objectID matches
	{
		object_array[_id.index]->setOn(_on);
		return 1;
	}
	else
		return -1;
}

int ObjectManager::RemoveObject(ObjectID _id)
{
	if (_id.revision == object_array[_id.index]->getID().revision)//Check if refision of objectID matches
	{
		counter++;//Raise counter

		ToggleObject(_id, false);//Call ToggleObject() to make function's ignore object
		
		//Change refision
		ObjectID id;
		id.index = _id.index;
		id.revision = counter;
		object_array[_id.index]->setID(id);

		//Add object to removed objects array
		removed_objects.push_back(id.index);	
		return 1;
	}
	else
		return 1;

}

/*
int ObjectManager::ClearComponents(ObjectID _id, MessageHandler &message)
{
	if (_id.revision == object_array[_id.index]->getID().revision)//Check if refision of objectID matches
	{
		for (int i = object_array[_id.index]->; i < object_array[_id.index]->getCompTypeSum(); i++)
		{
			messageData t;
			t.CompId = object_array[_id.index]->components.at(i)->getId();
			message.AddMessage(SYS::DEFAULT, (unsigned int)MESSAGE::REMOVE_COMPONENT);
		}
	}
	else
		return -1;
}*/

void ObjectManager::ClearAll()
{

}

Object* ObjectManager::GetObject(ObjectID _id)
{
	try
	{
		if (_id.revision == object_array[_id.index]->getID().revision)//Check if refision of objectID matches
			return object_array[_id.index];
		else
			throw -1;
	}
	catch (int e)
	{
		std::cout << e << " Could not find object with id " << _id.index << " and revision " << _id.revision << std::endl;
	}
	return nullptr;
}

Object* ObjectManager::GetObject(unsigned int _index)
{
	try
	{
		if (_index == object_array[_index]->getID().index)//Check if refision of objectID matches
			return object_array[_index];
		else
			throw - 1;
	}
	catch (int e)
	{
		std::cout << e << " Could not find object with id " << _index << std::endl;
	}
	return nullptr;
}

std::vector<Object*>::iterator ObjectManager::getObjectsBegin()
{
	return object_array.begin();
}

std::vector<Object*>::iterator ObjectManager::getObjectsEnd()
{
	return object_array.end();
}
