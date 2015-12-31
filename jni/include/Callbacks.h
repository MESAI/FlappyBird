/*
 * Callbacks.h
 *
 *  Created on: Dec 30, 2015
 *      Author: MESAI
 */

#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_

#include <jni.h>

class Callbacks{

public:
	/**
	   Setup a cached version of the JVM to execute the Callback.
	   @param the jvm pointer
	*/
	static void setupCallbacks(JavaVM * jvm);
	/**
	   Update the score on java side.
	   @param the score
	*/
	static void updateScoreCallBack(int score);
	/**
	   Notify the UI that the game is over
	*/
	static void gameOverCallBack();
};

#endif /* INCLUDE_CALLBACKS_H_ */
