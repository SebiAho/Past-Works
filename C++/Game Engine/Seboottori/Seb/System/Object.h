#pragma once
#include <map>
#include "Definitions.h"
#include "ObjectID.h"
#include "ComponentID.h"
#include "Component.h"

//Test
#include "../Components/GraphicsComponent.h"

namespace seb
{
	class Object//Program/Game object class
	{
	public:
		Object();
		~Object();

		ObjectID getID(){ return id; };
		void setID(ObjectID _id){ id = _id; };

		bool getOn(){ return On; };
		void setOn(bool _on){ On = _on; };//Sets object and all its components to on/off, does not set components on/off

		Component* getComponent(COMP _type);//Returns component of requested type, throws -1 on failure

		unsigned int getComponentList(){ return comp_type_sum; };
		int AddComponent(Component &_component);//Add new component to object, return's added components index if successfull, -1 otherwise

		/* Removes component from object, returns index of the removed component if succesfull, -1 otherwise,
			can invalidate existing indexes/references to components array,
			does not alter the component*/
		int RemoveComponent(Component &_component);
		int getCompTypeSum(){ return comp_type_sum; };//Returns sum of component type id's included in a object

		void Copy(const Object &_object);//Copies given object to current

	private:
		ObjectID id;//Identifier of object, set in ObjectManager's AddObject() function
		bool On;////Used to check if object is in use or not
		std::map<COMP,Component*> components;//Pointers to components used by the object
		unsigned int comp_type_sum;//Sum of component type id's included in a object

		friend class ObjectManager;

	};
}

