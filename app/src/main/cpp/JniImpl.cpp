//
// Created by byteFlow on 2019/7/9.
//
#include "util/LogUtil.h"
#include <MyGLRenderContext.h>
#include <EGLRender.h>
#include "jni.h"

#define NATIVE_RENDER_CLASS_NAME "com/byteFlow/app/MyNativeRender"
#define NATIVE_BG_RENDER_CLASS_NAME "com/byteFlow/app/egl/NativeEglRender"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

static JNINativeMethod g_RenderMethods[] = {};

static JNINativeMethod g_BgRenderMethods[] = {};

static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum)
{
	LOGCATE("RegisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == NULL)
	{
		LOGCATE("RegisterNativeMethods fail. clazz == NULL");
		return JNI_FALSE;
	}
	if (env->RegisterNatives(clazz, methods, methodNum) < 0)
	{
		LOGCATE("RegisterNativeMethods fail");
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className)
{
	LOGCATE("UnregisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == NULL)
	{
		LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
		return;
	}
	if (env != NULL)
	{
		env->UnregisterNatives(clazz);
	}
}

// call this func when loading lib
extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p)
{
	LOGCATE("===== JNI_OnLoad =====");
	jint jniRet = JNI_ERR;
	JNIEnv *env = NULL;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return jniRet;
	}

	jint regRet = RegisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME, g_RenderMethods,
										sizeof(g_RenderMethods) /
										sizeof(g_RenderMethods[0]));
	if (regRet != JNI_TRUE)
	{
		return JNI_ERR;
	}

	regRet = RegisterNativeMethods(env, NATIVE_BG_RENDER_CLASS_NAME, g_BgRenderMethods,
										sizeof(g_BgRenderMethods) /
										sizeof(g_BgRenderMethods[0]));
	if (regRet != JNI_TRUE)
	{
		return JNI_ERR;
	}

	return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p)
{
	JNIEnv *env = NULL;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return;
	}

	UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);

	UnregisterNativeMethods(env, NATIVE_BG_RENDER_CLASS_NAME);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_init(JNIEnv *env, jobject thiz) {
	MyGLRenderContext::GetInstance();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_unInit(JNIEnv *env, jobject thiz) {
	MyGLRenderContext::DestroyInstance();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_setParamsInt(JNIEnv *env, jobject thiz, jint param_type,
												  jint index, jint value1) {
	MyGLRenderContext::GetInstance()->SetParamsInt(param_type, index, value1);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_setParamsFloat(JNIEnv *env, jobject thiz, jint param_type,
													jfloat value0, jfloat value1) {
	MyGLRenderContext::GetInstance()->SetParamsFloat(param_type, value0, value1);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_updateTransformMatrix(JNIEnv *env, jobject thiz,
														   jfloat rotate_x, jfloat rotate_y,
														   jfloat scale_x, jfloat scale_y) {
	MyGLRenderContext::GetInstance()->UpdateTransformMatrix(rotate_x, rotate_y, scale_x, scale_y);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_setImageData(JNIEnv *env, jobject thiz, jint format,
												  jint width, jint height, jbyteArray imageData) {
	int len = env->GetArrayLength (imageData);
	uint8_t* buf = new uint8_t[len];
	env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte*>(buf));
	MyGLRenderContext::GetInstance()->SetImageData(format, width, height, buf);
	delete[] buf;
	env->DeleteLocalRef(imageData);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_setImageDataWithIndex(JNIEnv *env, jobject thiz, jint index,
														   jint format, jint width, jint height,
														   jbyteArray imageData) {
	int len = env->GetArrayLength (imageData);
	uint8_t* buf = new uint8_t[len];
	env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte*>(buf));
	MyGLRenderContext::GetInstance()->SetImageDataWithIndex(index, format, width, height, buf);
	delete[] buf;
	env->DeleteLocalRef(imageData);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_setAudioData(JNIEnv *env, jobject thiz,
												  jshortArray audio_data) {
	int len = env->GetArrayLength(audio_data);
	short *pShortBuf = new short[len];
	env->GetShortArrayRegion(audio_data, 0, len, reinterpret_cast<jshort*>(pShortBuf));
	MyGLRenderContext::GetInstance()->SetParamsShortArr(pShortBuf, len);
	delete[] pShortBuf;
	env->DeleteLocalRef(audio_data);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_onSurfaceCreated(JNIEnv *env, jobject thiz) {
	MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_onSurfaceChanged(JNIEnv *env, jobject thiz, jint width,
													  jint height) {
	MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_MyNativeRender_onDrawFrame(JNIEnv *env, jobject thiz) {
	MyGLRenderContext::GetInstance()->OnDrawFrame();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_egl_NativeEglRender_eglRenderInit(JNIEnv *env, jobject thiz) {
	EGLRender::GetInstance()->Init();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_egl_NativeEglRender_eglRenderSetImageData(JNIEnv *env, jobject thiz,
																jbyteArray data, jint width,
																jint height) {
	int len = env->GetArrayLength (data);
	uint8_t* buf = new uint8_t[len];
	env->GetByteArrayRegion(data, 0, len, reinterpret_cast<jbyte*>(buf));
	EGLRender::GetInstance()->SetImageData(buf, width, height);
	delete[] buf;
	env->DeleteLocalRef(data);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_egl_NativeEglRender_eglRenderSetIntParams(JNIEnv *env, jobject thiz,
																jint param_type, jint param) {
	EGLRender::GetInstance()->SetIntParams(param_type, param);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_egl_NativeEglRender_eglRenderDraw(JNIEnv *env, jobject thiz) {
	EGLRender::GetInstance()->Draw();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_byteFlow_app_egl_NativeEglRender_eglRenderUnInit(JNIEnv *env, jobject thiz) {
	EGLRender::GetInstance()->UnInit();
}