#include <jni.h>

#define JNI_NAME(name) Java_com_template_android_NativeInterface_##name

#include "Application.h"

static Application application;

extern "C" {

JNIEXPORT void JNI_NAME(onCreate)() {
	application.onCreate();
}

JNIEXPORT void JNI_NAME(onDrawFrame)() {
	application.onUpdate();
	application.onDraw();
}

JNIEXPORT void JNI_NAME(onSurfaceChanged)(int width, int height) {
	application.onResize(width, height);
}

JNIEXPORT void JNI_NAME(onSurfaceCreated)() {
}

JNIEXPORT void JNI_NAME(onTouchEvent)(int x, int y, int type) {
	application.onTouch(TouchEvent(x, y, TouchEvent::Down));
}

}

#undef JNI_NAME
