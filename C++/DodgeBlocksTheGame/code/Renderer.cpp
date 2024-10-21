#include "Renderer.h"
#include <cassert>

#include <android/log.h>

#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NatSample", __VA_ARGS__)
Renderer::Renderer():initialized(false)
{
	for(int i = 0; i < 4; i++)
	{
		color[i] = 0.0f;
	}
}


Renderer::~Renderer()
{
}

int Renderer::Init_context(Android_Engine& _engine)
{
	
    if (_engine.display == EGL_NO_DISPLAY)//Ensure that OpenGl is initialized only once
    {
		
		EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		assert(display);

		//Init EGL (res variable used in debugging)
		EGLBoolean res = eglInitialize(display, 0, 0);
		assert(res =! EGL_FALSE);
		
		//Declare the attributes for window
		const EGLint RGBX_8888_ATTRIBS[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
			EGL_WINDOW_BIT, 
			EGL_BLUE_SIZE, 8, 
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8, 
			EGL_DEPTH_SIZE, 8, 
			EGL_NONE
		};

		const EGLint RGB_565_ATTRIBS[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
			EGL_WINDOW_BIT, 
			EGL_BLUE_SIZE, 5, 
			EGL_GREEN_SIZE, 6,
			EGL_RED_SIZE, 5, 
			EGL_DEPTH_SIZE, 8, 
			EGL_NONE
		};

		const EGLint* attribList;

		int windowFormat = ANativeWindow_getFormat(_engine.app->window);

		if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888))
		{
			attribList = RGBX_8888_ATTRIBS;
		}
		else
		{
			attribList = RGB_565_ATTRIBS;
		}

		//Choose the correct config
		EGLConfig config;
		EGLint numConfigs;
		res = eglChooseConfig(display, attribList, &config, 1, &numConfigs);
		assert(res);

		//Set the correct format
		EGLint format;
		res = eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

		assert(res);
		
		//Set screen geometry and create screen rendering surface
		int32_t setBufRes = ANativeWindow_setBuffersGeometry(_engine.app->window, 0, 0, format);
		assert(setBufRes == 0);

		EGLDisplay surface;
		EGLNativeWindowType windowType;
		surface = eglCreateWindowSurface(display, config, _engine.app->window, NULL);
		assert(surface != EGL_NO_SURFACE);

		//Set up the rendering context
		EGLContext context;
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
		context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
		assert(context != EGL_NO_CONTEXT);

		//Make rendering surface and context current
		res = eglMakeCurrent(display, surface, surface, context);
        assert(res);

		//Get the screen dimenssions
		EGLint w, h;
        res = eglQuerySurface(display, surface, EGL_WIDTH, &w);
		assert(res);
		_engine.width = w;
		
        res = eglQuerySurface(display, surface, EGL_HEIGHT, &h);
        assert(res);
		_engine.height = h;
		
		//Store the values 
		_engine.display = display;
		_engine.renderSurface = surface;
		_engine.context = context;
		
		glEnable(GL_DEPTH_TEST);
 	}
	initialized = true;
	return 0;
}

int Renderer::Destroy(Android_Engine& _engine)
{
	if (_engine.display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(_engine.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (_engine.context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(_engine.display, _engine.context);
        }
        if (_engine.renderSurface != EGL_NO_SURFACE)
        {
            eglDestroySurface(_engine.display, _engine.renderSurface);
        }
        eglTerminate(_engine.display);
    }
    _engine.display = EGL_NO_DISPLAY;
    _engine.context = EGL_NO_CONTEXT;
    _engine.renderSurface = EGL_NO_SURFACE;
	
	return 0;
}

int Renderer::Init_draw(Android_Engine& _engine)
{
	_engine.shaderProgram = Init_ShaderProgram();
	if (!_engine.shaderProgram)
	{
		LOG("Could not create program.");
	}
	_engine.gvPositionHandle = glGetAttribLocation(_engine.shaderProgram, "vPosition");
	_engine.textureHandle = glGetAttribLocation(_engine.shaderProgram, "texturecoord");
	_engine.textureID = glGetAttribLocation(_engine.shaderProgram, "objectSampler");

	glEnableVertexAttribArray(_engine.gvPositionHandle);
	glEnableVertexAttribArray(_engine.textureHandle);

	initShaderVariables(_engine);

	return 0;
}

int Renderer::Start_frame(Android_Engine& _engine)
{
	//Check that display is created
	if(_engine.display == nullptr)
	{
		return 1;
	}
	//Enable GL states
	glEnable(GL_DEPTH_TEST);
	
	//Fill the screen with color
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	return 0;
}

int Renderer::End_frame(Android_Engine& _engine)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0u);
	eglSwapBuffers(_engine.display, _engine.renderSurface);
}

int Renderer::Draw(Graphic_Object& _object, GTexture& _texture, Android_Engine& _engine)
{
	//Set position
	GLint unifWorld = glGetUniformLocation(_engine.shaderProgram, "unifWorld");
	assert(unifWorld != -1);

	glm::mat4 worldTransform = glm::translate(_object.getPosition());
	glUniformMatrix4fv(unifWorld, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));

	//Vertex
	glBindBuffer(GL_ARRAY_BUFFER, *_object.vertex_buffer);
	glVertexAttribPointer(_engine.gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(0));

	//Texture
	glEnableVertexAttribArray(_engine.textureHandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	//LOG("Texture id: %i", _texture.id);
	glUniform1i(_engine.textureID, 0);

	glBindBuffer(GL_ARRAY_BUFFER, *_object.texture_buffer);
	glVertexAttribPointer(_engine.textureHandle, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

	//Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_object.index_buffer);
	glDrawElements(GL_TRIANGLES, _object.index_amount, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(0));


	return 0;
}

GLuint Renderer::Init_ShaderProgram()
{
	//Load Shaders
	GLuint vertexShader = Init_VertexShader();
	assert(vertexShader );
	
	GLuint fragmentShader = Init_FragmentShader();
	assert(fragmentShader);
	
	//Create program object
	GLuint programObject = glCreateProgram();
	assert(programObject);
	
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	
	// Bind variables
	glBindAttribLocation(programObject, 0, "vPosition");
	
	//Link program object
	glLinkProgram(programObject);
	
	//Check link status
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (linked != GL_TRUE) 
	{
		GLint bufLength = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &bufLength);
		if (bufLength) 
		{
			char* buf = (char*) malloc(bufLength);
		
			if (buf)
			{
				glGetProgramInfoLog(programObject, bufLength, NULL, buf);
				LOG("Could not link program: %s\n", buf);
				free(buf);
			}
		}
            glDeleteProgram(programObject);
            programObject = 0;
	}
	if(linked == GL_TRUE)
	{
		LOG("Link succes");
	}

	return programObject;
}

GLuint Renderer::Load_Shader(GLenum shaderType, const char *shaderSrc)
{
	//Create shader object
	GLuint shader = glCreateShader(shaderType);
	assert(shader > 0);
	if(shader == 0)
	{
		LOG("Shader 0");
	}
	
	//Load shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);
	
	//Compile shader
	glCompileShader(shader);
		
	//Check compile status
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	assert(compiled);
	
	return shader;
}

int Renderer::initShaderVariables(Android_Engine& _engine)
{
	GLint unifProjection;
	GLint unifView;
	GLint unifWorld;
	float aspect = static_cast<float>(_engine.width)/_engine.height;

	//Projections, views, etc
	glUseProgram(_engine.shaderProgram);

	//Setting unforms(projection)
	unifProjection = glGetUniformLocation(_engine.shaderProgram, "unifProjection");	
	assert(unifProjection != -1);
	
	glm::mat4 projectionTransform = glm::perspective(glm::radians(60.0f), aspect, 0.01f, 1000.0f);
	glUniformMatrix4fv(unifProjection, 1, GL_FALSE, reinterpret_cast<float*>(&projectionTransform));
	
	//View
	unifView = glGetUniformLocation(_engine.shaderProgram, "unifView");	
	assert(unifView != -1);
	
	glm::mat4 viewTransform = glm::translate(glm::vec3(0.0f, -0.5f, -200.0f));
	glUniformMatrix4fv(unifView, 1, GL_FALSE, reinterpret_cast<float*>(&viewTransform));
	
	//World
	unifWorld = glGetUniformLocation(_engine.shaderProgram, "unifWorld");	
	assert(unifWorld != -1);
	
	glm::mat4 worldTransform = glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));

	glUniformMatrix4fv(unifWorld, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));
	
	glUseProgram(0u);
	
	//
	return 0;
}

GLuint Renderer::Init_VertexShader()
{
	char vShader[] =
		"uniform mat4 unifProjection;\n"
		"uniform mat4 unifView;\n"
		"uniform mat4 unifWorld;\n"

		"attribute vec3 vPosition; \n"
		"attribute vec3 textcoord;\n"
		"varying vec2 textCoord;\n"

		"void main() \n"
		"{ \n"
		" gl_Position = unifProjection*unifView*unifWorld*vec4(vPosition, 1.0); \n"
		" textCoord = textcoord.xy;\n"
	"} \n";
	
	//Load Shader
	GLuint vertexShader = Load_Shader(GL_VERTEX_SHADER, vShader);
	LOG("vertex succes");
	
	return vertexShader;
}

GLuint Renderer::Init_FragmentShader()
{
	char fShader[] =
		"precision mediump float; \n"
		"varying vec2 textCoord;\n"
		"uniform sampler2D objectSampler; \n"

		"void main() \n"
		"{ \n"
		" gl_FragColor = texture2D(objectSampler, textCoord);\n"
	"} \n";
	
	//Load Shader
	GLuint fragmentShader = Load_Shader(GL_FRAGMENT_SHADER, fShader);
	LOG("fragment succes");
	
	return fragmentShader;
}

void Renderer::setClear_color(GLclampf _red, GLclampf _green, GLclampf _blue, GLclampf _alpha)
{	
	color[0] = _red;
	color[1] = _green;
	color[2] = _blue;
	color[3] = _alpha;
};

void Renderer::MoveView(Android_Engine& _engine, float _speed)
{
	GLint unifView = glGetUniformLocation(_engine.shaderProgram, "unifView");
	assert(unifView != -1);

	glm::mat4 viewTransform = glm::translate(glm::vec3(_speed, -0.5f, -200.0f))*glm::rotate(glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(unifView, 1, GL_FALSE, reinterpret_cast<float*>(&viewTransform));
}

void Renderer::GetAllErrors(int _id)
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		switch (error)
		{
		case GL_NO_ERROR:
			LOG("%i GL_NO_ERROR, No error has been recorded.", _id);
				break;

		case GL_INVALID_ENUM:
			LOG("%i GL_INVALID_ENUM, An unacceptable value is specified for an enumerated argument.", _id);
			break;

		case GL_INVALID_VALUE:
			LOG("%i GL_INVALID_VALUE, A numeric argument is out of range.", _id);
				break;

		case GL_INVALID_OPERATION:
			LOG("%i GL_INVALID_OPERATION, The specified operation is not allowed in the current state.", _id);
				break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			LOG("%i GL_INVALID_FRAMEBUFFER_OPERATION, The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete(i.e.the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE).The offending command is ignored and has no other side effect than to set the error flag.", _id);
				break;

		case GL_OUT_OF_MEMORY:
			LOG("%i GL_OUT_OF_MEMORY, There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.", _id);
				break;
		}
	}
}