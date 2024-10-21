#include "Android_Engine.h"


Android_Engine::Android_Engine() 
	: display(EGL_NO_DISPLAY)
	, renderSurface(EGL_NO_DISPLAY)
	, context(EGL_NO_DISPLAY)
	, width(0), height(0)
{
}


Android_Engine::~Android_Engine()
{
}
