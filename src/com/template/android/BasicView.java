package com.template.android;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import android.opengl.GLES20;

class BasicView extends GLSurfaceView {

	public BasicView(Context context) {
		super(context);
		setEGLContextClientVersion(2);
		setRenderer(new BasicRenderer(context));
	}

	@Override
	public boolean onTouchEvent(final MotionEvent event) {
		queueEvent(new Runnable() {
			public void run() {
				NativeInterface.onTouchEvent(0, 0, 0);
			}
		});

		return true;
	}

}
