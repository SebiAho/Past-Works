#pragma once
#include "Android_Engine.h"
#include "Graphic_Object.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	int Init_context(Android_Engine& _engine);
	int Destroy(Android_Engine& _engine);
	int Init_draw(Android_Engine& _engine);//Handles initialization needed after context but before draw
	int Start_frame(Android_Engine& _engine);//Start drawing on the frame
	int End_frame(Android_Engine& _engine);//End drawing and swap buffers to visible
	int Draw(Graphic_Object& _object, GTexture& _texture, Android_Engine& _engine);

	void setClear_color(GLclampf _red, GLclampf _green, GLclampf _blue, GLclampf _alpha);
	bool getInitialized(){return initialized;}
	bool setInitialized(bool _value){initialized = _value;}

	void MoveView(Android_Engine& _engine, float _speed);

	void GetAllErrors(int _id);//Gets all potenttial errors on glgeterror function
private:
	GLuint Load_Shader(GLenum shaderType, const char *shaderSrc);
	GLuint Init_VertexShader();
	GLuint Init_FragmentShader();
	GLuint Init_ShaderProgram();
	int initShaderVariables(Android_Engine& _engine);

	GLclampf color[4];
	bool initialized;
};

