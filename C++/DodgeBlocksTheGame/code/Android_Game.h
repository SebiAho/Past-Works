#pragma once
#include <android_native_app_glue.h>

#include "Android_Engine.h"
#include "Renderer.h"
#include "Input.h"
#include "Game_Logic.h"

class Android_Game
{
public:
	Android_Game(android_app* _app);
	~Android_Game();
	
	void Game_loop(android_app* _app, Android_Engine& _engine);
	static void processCommand(android_app* _app, int command);
private:
	bool isRunning;
	static Android_Engine engine;
	static Renderer renderer;
	Game_Logic logic;
};