package com.byteFlow.app;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static com.byteFlow.app.MyNativeRender.SAMPLE_TYPE;
import static com.byteFlow.app.MyNativeRender.SAMPLE_TYPE_SET_GRAVITY_XY;
import static com.byteFlow.app.MyNativeRender.SAMPLE_TYPE_SET_TOUCH_LOC;

public class MyGLRender implements GLSurfaceView.Renderer {
    private static final String TAG = "MyGLRender";
    private MyNativeRender mNativeRender;
    private int mSampleType;

    MyGLRender() {
        mNativeRender = new MyNativeRender();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mNativeRender.onSurfaceCreated();
        Log.e(TAG, "onSurfaceCreated() called with: GL_VERSION = [" + gl.glGetString(GL10.GL_VERSION) + "]");
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mNativeRender.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mNativeRender.onDrawFrame();
    }

    public void init() {
        mNativeRender.init();
    }

    public void unInit() {
        mNativeRender.unInit();
    }

    public void setParamsInt(int paramType, int index, int value1) {
        if (paramType == SAMPLE_TYPE) {
            mSampleType = index;
        }
        mNativeRender.setParamsInt(paramType, index, value1);
    }

    public void setTouchLoc(float x, float y)
    {
        mNativeRender.setParamsFloat(SAMPLE_TYPE_SET_TOUCH_LOC, x, y);
    }

    public void setGravityXY(float x, float y) {
        mNativeRender.setParamsFloat(SAMPLE_TYPE_SET_GRAVITY_XY, x, y);
    }

    public void setImageData(int format, int width, int height, byte[] bytes) {
        mNativeRender.setImageData(format, width, height, bytes);
    }

    public void setImageDataWithIndex(int index, int format, int width, int height, byte[] bytes) {
        mNativeRender.setImageDataWithIndex(index, format, width, height, bytes);
    }

    public void setAudioData(short[] audioData) {
        mNativeRender.setAudioData(audioData);
    }

    public int getSampleType() {
        return mSampleType;
    }

    public void updateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY)
    {
        mNativeRender.updateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
    }

}
