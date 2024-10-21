#pragma once
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include "glm/glm.hpp"
#include "Input.h"

class Android_Engine//Used to hold program data
{
public:
	Android_Engine();
	~Android_Engine();

	struct android_app* app;

	//Graphic rendering data
	EGLDisplay display;
	EGLSurface renderSurface;
	EGLContext context;
	int32_t width;
	int32_t height;
	
	//Shader & view data
	GLint shaderProgram;
	GLuint gvPositionHandle;
	GLuint gvColorHandle;
	GLuint textureHandle;
	GLuint textureID;
	
	//Input data
	struct Saved_state
	{	
		int32_t x_start, x_end;
		int32_t y_start, y_end;
		int direct_x;
	};

	struct Saved_state input_state;

};

