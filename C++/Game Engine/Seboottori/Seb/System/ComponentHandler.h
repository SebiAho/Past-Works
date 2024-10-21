#pragma once
#include <vector>
#include <unordered_map>
#include "Component.h"
#include "ObjectID.h"
#include "Object.h"
#include <type_traits>

namespace seb
{
	class ComponentHandler//Base class for handling components,
	{
	public:
		ComponentHandler();
		~ComponentHandler();
		
		/*Add component to handler, _object = object that the object is assigned, _comp = component, type of _comp must inherit seb::Component as base class*/
		template<typename T>
		ComponentID AddComponent(Object& _object, T& _comp)
		{
			ComponentID id;
			id.index = -1;
			id.revision = counter;

			//Check that component is same as the handler, and that component of same type is not alredy inluded in object
			if ((_comp.type != type) && (unsigned int)_comp.type & _object.getComponentList())
				return id;

			//Check if removed_components array is empty
			if (removed_components.empty() == true)
			{
				//Assign component to a new slot in components_array
				component_array.push_back(new T(_comp));
				id.index = component_array.size() - 1;
				component_array.back()->id = id;
				component_array.back()->objectId = _object.getID();

				//Link component to object
				_object.AddComponent(*component_array.back());
				return id;
			}
			else
			{
				//Assign component to an unused slot in component_array
				id.index = removed_components.back();
				_comp.id = id;
				_comp.objectId = _object.getID();
				component_array.at(id.index)->Copy(_comp);
				removed_components.pop_back();
				return id;
			}
		};

		int RemoveComponent(ObjectID _objectId);//Removes component from use, requires id of object the component is assigned for, returns -1 on failure
		void ClearAll();//Clears all arrays, Use at your own risk, Not currently implemented
		COMP getType(){ return type; };
		bool getInUse(){ return inUse; };

		std::vector<Component*>::iterator getComponentsBegin();//Get iterator to first element of component_array
		std::vector<Component*>::iterator getComponentsEnd();//Get iterator to last element of component_array
		/*Adds component to array, requires component and object it is assigned, returns ComponentID with an index of -1 on failure*/

		
	private:
		std::vector<Component*> component_array;
		std::vector<unsigned int> removed_components;
		unsigned int counter; // Incremented by RemoveComponent(), given to new objects by AddComponent()

		COMP type;//Type id of component held in handler
		bool inUse;//Is handler currently in use
		friend class ComponentManager;
	};
}
