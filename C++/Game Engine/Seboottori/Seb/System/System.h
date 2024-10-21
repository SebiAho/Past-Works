#pragma once

#include "MessageHandler.h"
#include "Definitions.h"
#include "ObjectManager.h"

namespace seb
{
	class System//Base class for systems
	{
	public:
		System();
		System(unsigned int _id) :id(_id){};
		virtual ~System(){};

		virtual void Intitialize(ObjectManager &_objects){};//System initialization, components required by the system should be added to ComponentManager here
		virtual void Update(){};
		virtual void handleMessage(MessageHandler &_messages){};//Receive and send messages between systems, or use SYS enum from definitions
		unsigned int getId(){ return id; };
	
	private:
		unsigned int id;//System id, must be exponent of 2 (2, 4, 8, ...)
		
	};
}

