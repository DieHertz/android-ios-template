LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := template
LOCAL_CPPFLAGS  := -Wall -std=c++11 -DPLATFORM_ANDROID
LOCAL_LDLIBS    := -lGLESv2 -llog
LOCAL_SRC_FILES := Application.cpp main.cpp TouchEvent.cpp

include $(BUILD_SHARED_LIBRARY)
