LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := native-activity
LOCAL_SRC_FILES :=				\
	android_native_app_glue.c	\
	Main.cpp					\
	Renderer.cpp				\
	Android_Engine.cpp	\
	Android_Game.cpp		\
	Input.cpp					\
	File_Loader.cpp	\
	lodepng.cpp	\
	Graphic_Object.cpp  \
	Game_Logic.cpp

LOCAL_CXXFLAGS := -std=gnu++11
LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2

include $(BUILD_SHARED_LIBRARY)