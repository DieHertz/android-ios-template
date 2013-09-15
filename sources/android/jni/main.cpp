#include "Application.h"
#include "TouchEvent.h"

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JNI_NAME(name) Java_com_template_android_NativeInterface_##name

JNIEXPORT void JNI_NAME(onCreate)(JNIEnv*, jclass) {
    Application::getInstance()->onCreate();
}

JNIEXPORT void JNI_NAME(onSurfaceCreated)(JNIEnv*, jclass) {
    Application::getInstance()->onContextCreated();
}

JNIEXPORT void JNI_NAME(onSurfaceChanged)(JNIEnv*, jclass, jint width, jint height) {
    Application::getInstance()->onResize(width, height);
}

JNIEXPORT void JNI_NAME(onDrawFrame)(JNIEnv*, jclass) {
    Application::getInstance()->onUpdate();
    Application::getInstance()->onDraw();
}

JNIEXPORT void JNI_NAME(onTouchEvent)(JNIEnv*, jclass, jfloat x, jfloat y, jint type, jint index) {
    Application::getInstance()->onTouch(TouchEvent(x, y, TouchEvent::Down, index));
}

JNIEXPORT jboolean JNI_NAME(onBackPressed)(JNIEnv*, jclass) {
    return Application::getInstance()->onBackPressed();
}

#ifdef __cplusplus
}
#endif

#undef JNI_NAME
