#include "MessageHandler.h"
using namespace seb;

MessageHandler::MessageHandler()
{
}


MessageHandler::~MessageHandler()
{
}

void MessageHandler::AddMessage(Message _message)
{
	message_array.push_back(_message);
}

void MessageHandler::AddMessage(SYS _systemID, unsigned int _messageID)
{
	AddMessage(Message(_systemID, _messageID));
}

void MessageHandler::AddMessage(SYS _systemID, unsigned int _messageID, messageData _data)
{
	AddMessage(Message(_systemID, _messageID, _data));
}

Message MessageHandler::SendMessage(SYS _systemID)
{
	if (UnhandledMessages() == true)
	{
		if (message_array.back().systemID == _systemID)//Check system id
		{
			Message m = message_array.back();
			message_array.pop_back();
			return m;
		}
		else if (message_array.back().systemID == SYS::ALL)//Gives system a copy of SYS::ALL message (message is not removed from array)
		{
			Message m = message_array.back();
			return m;
		}
	}
	return Message(SYS::DEFAULT, -1);
}

bool MessageHandler::DiscardMessage(unsigned int _systems)
{
	if (!(_systems & (unsigned int)message_array.back().systemID) || _systems == (unsigned int)SYS::DEFAULT)//Check if message systemID matches used systems
	{
		message_array.pop_back();
		return true;
	}
	return false;
}