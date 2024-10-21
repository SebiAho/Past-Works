#pragma once
namespace seb
{
	class WindowHandler//Base class for handling render window 
	{
	public:
		WindowHandler();
		~WindowHandler();
		virtual void Clear(){};
		virtual void EndDraw(){};

	};
}
