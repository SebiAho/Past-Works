#pragma once
#include <vector>
#include <unordered_map>
#include "Component.h"
#include "ObjectID.h"
#include "Object.h"
#include "ComponentHandler.h"

namespace seb
{
	class ComponentManager//Manages component handler classes
	{
	public:
		ComponentManager();
		~ComponentManager();

		int addHandler(COMP _type);//_type = component type id, returns type id of the new handler on succes, -1 otherwise
		int removeHandler(COMP _type);//_type = component type id, returns type of the removed handler on success, -1 otherwise
		void UseHandler(COMP _type, bool _use);//Toggles handlers on/off, by changing the state of inUSe variable
		/*returns handler by index, _index = index to handler, throws exeption -1 on failure*/
		ComponentHandler& getHandler(COMP _type);
		
		unsigned int getCompTypeSum(){ return comp_type_sum; };//Handlers the sum of handler types held in the manager
	private:
		std::unordered_map<COMP, ComponentHandler> handler_map;
		unsigned int comp_type_sum;//Holds sum of component type values of included handler, used to check if certain components already have a handler
	
	};
}
