#pragma once
#include <vector>
#include <map>

#include "Definitions.h"
#include "MessageHandler.h"
#include "System.h"
#include "ObjectManager.h"
#include "ComponentManager.h"


namespace seb
{
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		int AddSystem(System* _system);//Adds a system to system_array if it's id does not match prefious systems, returns index of added system
		int RemoveSystem();//Removes system from system_array, Not implemented

		void Initialize();//Handles system intialization, by default
		void Update();//Handles system updating
		
		MessageHandler &getMessageHandler(){ return messages; };
		System* getSystem(SYS _sys);//Returns pointer to system if succesfull, throws -1 otherwise
		bool getRunning(){ return running; };

		ObjectManager& getObjectManager(){ return objects; };//Get access to object manager

	private:
		unsigned int system_id_sum;//Stores the sum of system id's, used to check included systems (through binary comparison)
		MessageHandler messages;
		std::vector<System*> system_array;
		std::map<seb::SYS, int> sys_index_map;//Links system id to its current index
		bool running;//program is running = true

		ObjectManager objects;//Holds objects used by the system

		void DistributeMessages();//Distriputes messages to systems
	};
}
