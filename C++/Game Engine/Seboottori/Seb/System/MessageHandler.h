#pragma once
#include "Definitions.h"
#include <vector>
#include "ObjectID.h"
#include "ComponentID.h"

namespace seb
{
	union messageData
	{
		bool b;
		ObjectID ObId;
		ComponentID CompId;
	};

	struct Message
	{
		Message(SYS _systemID, unsigned int _messageID) :systemID(_systemID), messageID(_messageID){ data.b = false; };
		Message(SYS _systemID, unsigned int _messageID, messageData _data) :systemID(_systemID), messageID(_messageID), data(_data){};
		~Message(){};

		SYS systemID;
		unsigned int messageID;
		messageData data;
	
	};

	class MessageHandler//Handles distripution and storage of system messages
	{
	public:
		MessageHandler();
		~MessageHandler();

		/*SYS::ALL allows message to be send to every systems*/
		void AddMessage(Message _message);//Adds message to the message array
		void AddMessage(SYS _systemID, unsigned int _messageID);
		void AddMessage(SYS _systemID, unsigned int _messageID, messageData _data);
		Message SendMessage(SYS _systemID);//Checks system id and return and removes first message from array if a match or Message(SYS::DEFAULT, -1) if not
		bool DiscardMessage(unsigned int _systems);//Discards unclaimed and SYS::ALL type messages, call after looping trough all systems, _systems = the sum of system id's of all system's in use
		
		bool UnhandledMessages(){ return !message_array.empty(); };//Return true if messages array is not empty


	private:
		std::vector<Message> message_array;
	};
}
