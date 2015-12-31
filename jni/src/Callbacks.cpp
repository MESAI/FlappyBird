/*
 * Callbacks.cpp
 *
 *  Created on: Dec 30, 2015
 *      Author: MESAI
 */

#include "../include/Callbacks.h"

// JVM
static JavaVM * g_Jvm; // callbacks

void Callbacks::setupCallbacks(JavaVM * jvm)
{
	g_Jvm = jvm;
}

void Callbacks::updateScoreCallBack(int score)
{
	JNIEnv *env;
	g_Jvm->AttachCurrentThread(&env, 0);
	jclass myClass = env->FindClass("com.mesai0.blogspot.ZeptoLabTest.MainActivity");
	jmethodID mid = env->GetStaticMethodID(myClass, "updateScore", "(I)V");
	env->CallStaticVoidMethod(myClass, mid, (jint)score);
}

void Callbacks::gameOverCallBack()
{
	JNIEnv *env;
	g_Jvm->AttachCurrentThread(&env, 0);
	jclass myClass = env->FindClass("com.mesai0.blogspot.ZeptoLabTest.MainActivity");
	jmethodID mid = env->GetStaticMethodID(myClass, "gameOver", "()V");
	env->CallStaticVoidMethod(myClass, mid);
}
