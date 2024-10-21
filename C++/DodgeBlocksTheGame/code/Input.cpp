#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

//Process the next input event.
int32_t Input::InputEvent_handle(struct android_app* app, AInputEvent* event) 
{
    Android_Engine* engine = (Android_Engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) 
	{
		if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN)
		{
			int action = AKeyEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
			if (action == AMOTION_EVENT_ACTION_DOWN)
			{
				engine->input_state.x_start = AMotionEvent_getX(event, 0);
				engine->input_state.y_start = AMotionEvent_getY(event, 0);
			}
			if (action == AMOTION_EVENT_ACTION_UP)
			{
				engine->input_state.x_end = AMotionEvent_getX(event, 0);
				engine->input_state.y_end = AMotionEvent_getY(event, 0);
				if ((engine->input_state.x_start - engine->input_state.x_end) < 0)//Right
				{
					engine->input_state.direct_x = -1;
				}
				if ((engine->input_state.x_start - engine->input_state.x_end) > 0)//Left
				{
					engine->input_state.direct_x = 1;
				}
			}
		}
        return 1;
    }

    return 0;
}
