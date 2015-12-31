#include <jni.h>
#include "include/Game.h"

/**
	This is the wrapper of the engine.
	It connects the Java code with the native code
	It also initialize the Callback functions to connect the engine with
	the java code.
*/
extern "C"
{

	static JavaVM *cachedJVM;

	JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
	{
	    cachedJVM = jvm;
	    return  0x00010006;
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_onSurfaceCreated
		(JNIEnv * env, jclass cls) {
		Callbacks::setupCallbacks(cachedJVM);
		Game::onSurfaceCreated();
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_onSurfaceChanged
		(JNIEnv * env, jclass cls, jint width, jint height) {
		Game::onSurfaceChanged(width, height);
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_onDrawFrame
		(JNIEnv * env, jclass cls) {
		Game::onDrawFrame();
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_onTouchEventDown
		(JNIEnv * env, jclass cls) {
		Game::onTouchEventDown();
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_onTouchEventUp
		(JNIEnv * env, jclass cls) {
		Game::onTouchEventUp();
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_resetGame
		(JNIEnv * env, jclass cls) {
		Game::newGame();
	}

	JNIEXPORT
	void JNICALL Java_com_mesai0_blogspot_ZeptoLabTest_Native_clean
		(JNIEnv * env, jclass cls) {
		Game::clean();
	}
}
