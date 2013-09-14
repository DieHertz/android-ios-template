package com.template.android;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;

class BasicRenderer implements GLSurfaceView.Renderer {

    public BasicRenderer(Context context) {
        mContext = context;

        NativeInterface.onCreate();
    }

    public void onDrawFrame(GL10 glUnused) {
        NativeInterface.onDrawFrame();
    }

    public void onSurfaceChanged(GL10 glUnused, int width, int height) {
        NativeInterface.onSurfaceChanged(width, height);
    }

    public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
        NativeInterface.onSurfaceCreated();
    }

    private Context mContext;

}
