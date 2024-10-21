#include "File_Loader.h"
#include <fstream>
#include <cassert>
#include <sstream>

#include "lodepng.h"
#include <set>

#include <GLES2/gl2.h>
#include <android/asset_manager.h>
#include <unistd.h>
#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NatSample", __VA_ARGS__)
#include "Renderer.h"

File_Loader::File_Loader()
{
}


File_Loader::~File_Loader()
{
}

void File_Loader::Load_OBJ(std::string _name, Graphic_Object &_object, Renderer &_renderer)
{
	std::ifstream stream;
	stream.open(_name);// , std::ios::in);//Open for reading
	assert(stream.is_open());

	std::string line;
	std::vector<GLfloat> vertex;
	std::vector<GLfloat> texture_coord;
	std::vector<GLbyte> index;
	std::vector<GLbyte> texture_index;

	while (!stream.eof())
	{
		std::getline(stream, line);
		if (line.substr(0, 2) == "v ")//string.substr erottaa parametreissä(pos, amount) annetun osan tekstisä omaksi merkki joukokseen
		{
			std::istringstream value(line.substr(2));//muuttaa tekstin luvuiksi, istring ostring käyttö riippuu käyttötarkoituksesta (stringstream omaa kummankin ominaisuudet) 
			GLfloat tempx, tempy, tempz;
			value >> tempx;
			value >> tempy;
			value >> tempz;

			vertex.push_back(tempx);
			vertex.push_back(tempy);
			vertex.push_back(tempz);
		}
		else if (line.substr(0, 3) == "vt ")
		{
			std::istringstream value(line.substr(2));
			GLfloat tempx, tempy, tempz;
			value >> tempx;
			value >> tempy;
			value >> tempz;

			texture_coord.push_back(tempx);
			texture_coord.push_back(tempy);
			texture_coord.push_back(tempz);
		}
		else if (line.substr(0, 2) == "f ")//Huomaa väli kirjaimen jälkeen (a/b, a = pos coord, b tecture = coord)
		{
			std::istringstream value(line.substr(2));
			GLuint tempP, tempText;
			//std::string testing(line.substr(2));

			//1st index
			value >> tempP;//Get position tindex
			value.ignore(1, '/');//Extract and discard / character
			value >> tempText;//Get texture index

			index.push_back(--tempP);//Place position indexes to vectors
			texture_index.push_back(tempText--);//Place texture indexes to vectors

			//2nd index
			value >> tempP;	
			value.ignore(1, '/');
			value >> tempText;

			index.push_back(--tempP);
			texture_index.push_back(tempText--);

			//3rd index	
			value >> tempP;	
			value.ignore(1, '/');	
			value >> tempText;
			
			index.push_back(--tempP);
			texture_index.push_back(--tempText);
			
		}
		else
		{
			//ignore
		}

	}
	for (int i = 0; i < index.size(); i++)
	{
		//LOG("%i", index.at(i));
	}

	//Vertex
	_object.vertex_amount = vertex.size();
	glGenBuffers(1, _object.vertex_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *_object.vertex_buffer);//Bind vertex array
	glBufferData(GL_ARRAY_BUFFER, _object.vertex_amount*sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	_renderer.GetAllErrors(10);

	//Textures
	_object.texture_amount = texture_coord.size();
	glGenBuffers(1, _object.texture_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *_object.texture_buffer);//Bind vertex array
	glBufferData(GL_ARRAY_BUFFER, _object.texture_amount*sizeof(GLfloat), texture_coord.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	_renderer.GetAllErrors(4);

	//Index
	_object.index_amount = index.size();
	_object.texture_index_amount = texture_index.size();
	glGenBuffers(1, _object.index_buffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_object.index_buffer);//Bind vertex array indexes
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _object.index_amount*sizeof(GLubyte), index.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	_renderer.GetAllErrors(3);

}



GTexture File_Loader::LoadPNG(const char* _filename, Renderer &_renderer)
{
	struct GTexture texture;

	std::vector<unsigned char> out;
	unsigned int width, height;
	
	unsigned int error = lodepng::decode(out, width, height, _filename);
	if (error != 0)
		LOG("decodePNG failed with error: %u", error);

	// Create one OpenGL texture
	glGenTextures(1, &texture.id);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture.id);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	texture.width = width;
	texture.width = height;
	_renderer.GetAllErrors(4);
	return texture;
}

void File_Loader::Access_Assets(android_app* _app)
{
	//Retrieve JNI handle
	JNIEnv* env = _app->activity->env;
	JavaVM* vm = _app->activity->vm;
	vm->AttachCurrentThread(&env, NULL);

	//Get handle on this NativeActivity instance
	jclass activityClass = env->GetObjectClass(_app->activity->clazz);

	// Get path to cache dir where assets will be extracted
	jmethodID getCacheDir = env->GetMethodID(activityClass, "getCacheDir", "()Ljava/io/File;");
	jobject file = env->CallObjectMethod(_app->activity->clazz, getCacheDir);
	jclass fileClass = env->FindClass("java/io/File");
	jmethodID getAbsolutePath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
	jstring jpath = (jstring)env->CallObjectMethod(file, getAbsolutePath);
	const char* app_dir = env->GetStringUTFChars(jpath, NULL);

	// chdir in the application cache directory
	//LOG("app_dir: %s", app_dir);
	chdir(app_dir);
	env->ReleaseStringUTFChars(jpath, app_dir);

	//Get the NativeActivity asset manager
	AAssetManager *mgr = _app->activity->assetManager;

	//Extract files from assets to cache
	AAssetDir* assetDir = AAssetManager_openDir(mgr, "");
	const char* filename = (const char*)NULL;
	while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
		AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_STREAMING);
		char buf[BUFSIZ];
		int nb_read = 0;
		FILE* out = fopen(filename, "w");
		while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
			fwrite(buf, nb_read, 1, out);
		fclose(out);
		AAsset_close(asset);
	}
	AAssetDir_close(assetDir);
	vm->DetachCurrentThread();
	
}