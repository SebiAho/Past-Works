#include "Android_Game.h"
#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NatSample", __VA_ARGS__)
#include <vector>

#include <android/asset_manager.h>
#include <unistd.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include "File_Loader.h"
#include "Game_Logic.h"


Android_Engine Android_Game::engine;
Renderer Android_Game::renderer;
//Test
const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,0.5f, -0.5f };

Android_Game::Android_Game(android_app* _app):isRunning(true)
{
	//Init program
	_app->userData = &engine;
	_app->onAppCmd = processCommand;
	_app->onInputEvent = Input::InputEvent_handle;
	engine.app = _app;
	//Start program loop
	Game_loop(_app, engine);
}


Android_Game::~Android_Game()
{
}



void Android_Game::Game_loop(android_app* _app, Android_Engine& _engine)
{
	Game_Logic game;
	
	//----------------------------------------
	//Read files
	File_Loader loader;
	loader.Access_Assets(_app);

	//Load object
	Graphic_Object box;
		
	GLuint buffers[2];
	bool assets_loaded = false;

	//Texturing
	struct GTexture texture;
	float move = 35.0f, location = 25.0f;
	while (isRunning)
	{
		
		int events;
		int input_event;
		android_poll_source* eventSource;
		
		while ((input_event=ALooper_pollAll(0, nullptr, &events, reinterpret_cast<void**>(&eventSource))) >= 0)
		{
			if (eventSource != nullptr)
				eventSource->process(_app, eventSource);
		
			// Process input events.
			if (_engine.input_state.direct_x == 1)
			{
				move = -35.0f;
				location = -25.0f;
				LOG("Mouse dir %f", move);
			}
			if (_engine.input_state.direct_x == -1)
			{
				move = 35.0f;
				location = 25.0f;
				LOG("Mouse dir %f", move);
			}

			if (_app->destroyRequested != 0)
			{
				isRunning = false;
				break;
			}
		}
		
		//Load assets
		if (!assets_loaded && renderer.getInitialized() == true)
		{
			loader.Load_OBJ("Block.obj", box, renderer);
			texture = loader.LoadPNG("Texture.png", renderer);

			assets_loaded = true;
		}
		//Update and draw
		if (renderer.getInitialized() && assets_loaded)
		{
			renderer.Start_frame(engine);
			glUseProgram(engine.shaderProgram);

			renderer.MoveView(engine, move);
			renderer.GetAllErrors(3);
			
			logic.Update(box, renderer, texture, _engine, location);
			renderer.End_frame(engine);
		}
	}

}

void Android_Game::processCommand(android_app* _app, int command)
{
	switch (command)
		{
		case APP_CMD_INIT_WINDOW:
		{
			renderer.Init_context(engine);
			renderer.Init_draw(engine);
			renderer.setClear_color(1.0f, 1.0f, 1.0f, 1.0f);
			renderer.GetAllErrors(0);
			
		}
		break;
	 
		case APP_CMD_DESTROY:
		{
			LOG("destroy");	
		}
		break;
		
		//Terminate window   
		case APP_CMD_TERM_WINDOW: 
		{
			renderer.Destroy(engine);
			renderer.setInitialized(false);
		}
		break;

		case APP_CMD_RESUME:
			{
			}
			break;
	 
		case APP_CMD_PAUSE:
			{
			}
			break;
		}
}