LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_SRC_DIR        := ../../../sources
JNI_SRC_DIR         := $(ROOT_SRC_DIR)/android/jni
COMMON_SRC_DIR      := $(ROOT_SRC_DIR)/common
PROJECT_SRC_DIR     := $(ROOT_SRC_DIR)/project

LOCAL_MODULE     := template
LOCAL_CPPFLAGS   := -Wall -Wno-format-security -std=c++11
LOCAL_LDLIBS     := -lGLESv2 -llog
LOCAL_C_INCLUDES := ../../sources/common
LOCAL_SRC_FILES  := \
    $(JNI_SRC_DIR)/main.cpp \
    $(COMMON_SRC_DIR)/Application.cpp \
    $(COMMON_SRC_DIR)/TouchEvent.cpp \
    $(COMMON_SRC_DIR)/GlHelper.cpp \
    $(COMMON_SRC_DIR)/ShaderProgram.cpp \
    $(COMMON_SRC_DIR)/RenderDevice.cpp

LOCAL_SRC_FILES += \
    $(PROJECT_SRC_DIR)/EntryPoint.cpp \
    $(PROJECT_SRC_DIR)/Template.cpp

include $(BUILD_SHARED_LIBRARY)
