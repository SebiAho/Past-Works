#pragma once
#include <string>
#include "Graphic_Object.h"
#include <GLES2/gl2.h>
#include <vector>
#include <Renderer.h>

#include <android_native_app_glue.h>

class File_Loader//Handles file loading
{
public:
	File_Loader();
	~File_Loader();

	void Load_OBJ(std::string _name, Graphic_Object &_object, Renderer &_renderer);//Loads obj waveform files to buffers

	GTexture LoadPNG(const char* _filename, Renderer &_renderer);

	void Access_Assets(android_app* _app);//Allows assets to be read in android
private:
};

