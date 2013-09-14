#include <jni.h>

#define JNI_NAME(name) Java_com_template_android_NativeInterface_##name

#include "Application.h"

static Application application;

extern "C" {

JNIEXPORT void JNI_NAME(onCreate)(JNIEnv*, jclass) {
    application.onCreate();
}

JNIEXPORT void JNI_NAME(onSurfaceCreated)(JNIEnv*, jclass) {
    application.onContextCreated();
}

JNIEXPORT void JNI_NAME(onSurfaceChanged)(JNIEnv*, jclass, jint width, jint height) {
    application.onResize(width, height);
}

JNIEXPORT void JNI_NAME(onDrawFrame)(JNIEnv*, jclass) {
    application.onUpdate();
    application.onDraw();
}

JNIEXPORT void JNI_NAME(onTouchEvent)(JNIEnv*, jclass, jfloat x, jfloat y, jint type, jint index) {
    application.onTouch(TouchEvent(x, y, TouchEvent::Down, index));
}

JNIEXPORT jboolean JNI_NAME(onBackPressed)(JNIEnv*, jclass) {
    return application.onBackPressed();
}

}

#undef JNI_NAME
