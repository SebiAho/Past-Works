#pragma once
#include "ObjectID.h"
#include "ComponentID.h"
#include "Definitions.h"

namespace seb
{
	class Component//Base class for object components
	{
	public:
		Component(COMP _type = COMP::DEFAULT) :type(_type), On(false){};
		virtual ~Component(){};

		ComponentID getId(){ return id; };
		ObjectID getObjectId(){ return objectId; };

		bool getOn(){ return On; };
		void setOn(bool _on){ On = _on; };
		
		COMP getType(){ return type; };

		void Copy(Component const& _comp)
		{
			id = _comp.id;
			objectId = _comp.objectId;
			type = _comp.type;
			On = _comp.On;
		}

	private:
		ComponentID id;
		ObjectID objectId;//Id to object component belongs to, index -1 means component is not in use
		COMP type;//Component type, must be exponent of 2 (2, 4, 8, ...), or use COMP enum from definitions
		bool On;//Used to check if component is in use or not

		friend class ComponentHandler;
	};
}

