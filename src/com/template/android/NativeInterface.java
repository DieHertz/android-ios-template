package com.template.android;

public class NativeInterface {

	public native static void onCreate();
	public native static void onDrawFrame();
	public native static void onSurfaceChanged(int width, int height);
	public native static void onSurfaceCreated();
	public native static void onTouchEvent(int type, int x, int y);

}
