#pragma once
#include <android_native_app_glue.h>
#include "Android_Engine.h"

class Input
{
public:
	Input();
	~Input();
	
	static int32_t InputEvent_handle(struct android_app* app, AInputEvent* event);
};
