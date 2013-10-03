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
        final int type;

        switch (event.getActionMasked()) {
        case MotionEvent.ACTION_DOWN:
            type = 0;
            break;

        case MotionEvent.ACTION_POINTER_DOWN:
            type = 0;
            break;

        case MotionEvent.ACTION_MOVE:
            type = 2;
            break;

        case MotionEvent.ACTION_UP:
            type = 1;
            break;

        case MotionEvent.ACTION_POINTER_UP:
            type = 1;
            break;

        case MotionEvent.ACTION_CANCEL:
            type = 3;
            break;

        default:
            return false;
        }

        queueEvent(new Runnable() {
            public void run() {
                NativeInterface.onTouchEvent(event.getX(), event.getY(), type, 0);
            }
        });

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
