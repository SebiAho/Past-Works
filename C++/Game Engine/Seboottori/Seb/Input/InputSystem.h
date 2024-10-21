#pragma once
#include "../System/System.h"

namespace seb
{
	class InputSystem : public System
	{
	public:
		InputSystem();
		~InputSystem();

		void Intitialize(ObjectManager &_objects);
		void Update();
		void handleMessage(MessageHandler &_messages);
	};
}
