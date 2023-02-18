package com.byteFlow.app.egl;

public class NativeEglRender {

    public native void eglRenderInit();

    public native void eglRenderSetImageData(byte[] data, int width, int height);

    public native void eglRenderSetIntParams(int paramType, int param);

    public native void eglRenderDraw();

    public native void eglRenderUnInit();
}
