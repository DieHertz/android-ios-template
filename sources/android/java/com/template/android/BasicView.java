package com.template.android;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

class BasicView extends GLSurfaceView {

    public BasicView(Context context) {
        super(context);

        setEGLContextClientVersion(2);
        setEGLConfigChooser(8, 8, 8, 8, 16, 8);
        setPreserveEGLContextOnPause(true);
        setRenderer(new Renderer());
    }

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        switch (event.getActionMasked()) {
        case MotionEvent.ACTION_DOWN:
            NativeInterface.onTouchEvent(event.getX(), event.getY(), 0, 0);
            break;

        case MotionEvent.ACTION_POINTER_DOWN:
            NativeInterface.onTouchEvent(event.getX(), event.getY(), 0, 0);
            break;

        case MotionEvent.ACTION_MOVE:
            NativeInterface.onTouchEvent(event.getX(), event.getY(), 2, 0);
            break;

        case MotionEvent.ACTION_UP:
            NativeInterface.onTouchEvent(event.getX(), event.getY(), 1, 0);
            break;

        case MotionEvent.ACTION_POINTER_UP:
            NativeInterface.onTouchEvent(event.getX(), event.getY(), 1, 0);
            break;

        case MotionEvent.ACTION_CANCEL:
            NativeInterface.onTouchEvent(event.getX(), event.getY(), 3, 0);
            break;
        }

        return true;
    }

    private static class Renderer implements GLSurfaceView.Renderer {

        public void onDrawFrame(GL10 glUnused) {
            NativeInterface.onDrawFrame();
        }

        public void onSurfaceChanged(GL10 glUnused, int width, int height) {
            NativeInterface.onSurfaceChanged(width, height);
        }

        public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
            NativeInterface.onSurfaceCreated();
        }

    }

}
