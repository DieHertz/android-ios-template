LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SOURCES_DIR      := ../../../sources/common

LOCAL_MODULE     := template
LOCAL_CPPFLAGS   := -Wall -Wno-format-security -std=c++11
LOCAL_LDLIBS     := -lGLESv2 -llog
LOCAL_C_INCLUDES := ../../sources/common
LOCAL_SRC_FILES  := \
    main.cpp \
    $(SOURCES_DIR)/Application.cpp \
    $(SOURCES_DIR)/TouchEvent.cpp \
    $(SOURCES_DIR)/GlHelper.cpp

include $(BUILD_SHARED_LIBRARY)
