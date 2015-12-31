/*
 * Logger.h
 *
 *  Created on: Dec 23, 2015
 *      Author: MESAI
 */

#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_

#include <android/log.h>
#include <string>

#define APPNAME "ZeptoLabTest"
/**
  Print a string value.
  @param string value.
*/
static void print(std::string msg)
{
	__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", msg.c_str());
}
/**
  Print an integer value.
  @param integer value.
*/
static void print(int msg)
{
	__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%i", msg);
}
/**
  Print a float value.
  @param float value.
*/
static void print(float msg)
{
	__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%f", msg);
}


#endif /* INCLUDE_LOGGER_H_ */
