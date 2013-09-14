LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := template
LOCAL_CPPFLAGS  := -Wall -Wno-format-security -std=c++11
LOCAL_LDLIBS    := -lGLESv2 -llog
LOCAL_SRC_FILES := \
    Application.cpp main.cpp TouchEvent.cpp \
    GlHelper.cpp

include $(BUILD_SHARED_LIBRARY)
