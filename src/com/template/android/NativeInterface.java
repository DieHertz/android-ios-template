package com.template.android;

public class NativeInterface {

    static {
        System.loadLibrary("template");
    }

    public static native void onCreate();
    public static native void onSurfaceCreated();
    public static native void onSurfaceChanged(int width, int height);
    public static native void onDrawFrame();
    public static native void onTouchEvent(float x, float y, int type, int index);

    public static native boolean onBackPressed();
    

}
