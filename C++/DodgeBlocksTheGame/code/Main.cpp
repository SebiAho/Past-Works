#include <android/log.h>
#include <android_native_app_glue.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NatSample", __VA_ARGS__)

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "Renderer.h"
#include "Android_Engine.h"
#include "Android_Game.h"
static void processCommand(android_app* application, int command);

	//Test
	Android_Engine engine;
	Renderer renderer;
	const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,0.5f, -0.5f };
	//
	
void android_main(android_app* application)
{
	//Check that android_native_app_glue isn't stripped
	app_dummy();
	Android_Game game(application);	
}