#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Object.h"
#include "ObjectID.h"
#include "MessageHandler.h"
#include "ComponentManager.h"

namespace seb
{
	class Object;//Required for friend class to work

	class ObjectManager//Handles program objects holds array of Objects
	{
	public:
		ObjectManager();
		~ObjectManager();

		ObjectID AddObject(Object& _object);//Add object object array, returns ObjectID with index to object
		int ToggleObject(ObjectID _id, bool _on);//Toggles object On/Off, return 1 on success
		int RemoveObject(ObjectID _id);//Sets object to unused, so it can be used again, return 1 on success
		//int ClearComponents(ObjectID _id, MessageHandler &message);//Sends messages to all systems in order to remove components belonging to object, return 1 on success
		void ClearAll();//Clears all arrays, Use at your own risk, Not currently implemented
		Object* GetObject(ObjectID _id);
		Object* GetObject(unsigned int _index);
		std::vector<Object*>::iterator getObjectsBegin();//Get iterator to first element of object_array
		std::vector<Object*>::iterator getObjectsEnd();//Get iterator to lastt element of object_array

		ComponentManager& getCompManager(){ return components; };//Returns component manager

	private:
		std::vector<Object*> object_array;//Array containing actual objects
		std::vector<unsigned int> removed_objects;//Contains a list of removed objects
		unsigned int counter;//Incremented by RemoveObject(), given to new objects by AddObject()
		ComponentManager components;//Holds components used by the object manager
		
	};
}
