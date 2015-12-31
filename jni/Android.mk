LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE    := game
LOCAL_CPPFLAGS  := -std=c++11
LOCAL_SRC_FILES := src/game.cpp src/bird.cpp src/Obstacle.cpp src/Callbacks.cpp jni.cpp
LOCAL_LDLIBS := -lGLESv2 -llog 
 
include $(BUILD_SHARED_LIBRARY)