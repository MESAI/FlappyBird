/*
 * ShaderUtility.h
 *
 *  Created on: Dec 23, 2015
 *      Author: MESAI
 */

#ifndef SRC_SHADERUTILITY_H_
#define SRC_SHADERUTILITY_H_

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>
#include <vector>
#include "logger.h"

	// bird vertex shader
	static std::string birdVertexShader =
			"uniform mat4 projectionMatrix;"
			"uniform mat4 transformation;"
			"attribute vec2 position;"
			"attribute vec4 inputTextureCoordinate;"
			"varying vec2 textureCoordinate;"
			"void main()"
			"{"
				"vec4 position4 = vec4(position,0,1);"
				"gl_Position = projectionMatrix * transformation * position4;"
				"textureCoordinate = inputTextureCoordinate.xy;"
			"}";

	// bird fragment shader
	static std::string birdFragmentShader =
			"varying highp vec2 textureCoordinate;"
			"const highp vec2 center = vec2(0.5, 0.5);"
			"const highp float radius = 0.5;"
			"void main()"
			"{"
				"highp float distanceFromCenter = distance(center, textureCoordinate);"
			 	"lowp float checkForPresenceWithinCircle = step(distanceFromCenter, radius);"
			 	"if (checkForPresenceWithinCircle > 0.0) {"
					"gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0) * checkForPresenceWithinCircle;"
				"}"
				"else {"
					"gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
				"}"
			"}";
	// obstacle vertex shader
	static std::string obstacleVertexShader =
				"uniform mat4 projectionMatrix;"
				"uniform mat4 transformation;"
				"attribute vec2 position;"
				"void main()"
				"{"
					"vec4 position4 = vec4(position,0,1);"
					"gl_Position = projectionMatrix * transformation * position4;"
				"}";
	// obstacle fragment shader
	static std::string obstacleFragmentShader =
				"void main()"
				"{"
					"gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"
				"}";

	/**
	   Create a shader.
	   @param the source code of shader.
	   @param the type of the shader.
	   @return the id of the shader.
	*/
	static GLuint createShader(std::string source,GLuint mode)
	{
		GLuint id = glCreateShader(mode);
		const char * csource =  source.c_str();
		glShaderSource(id,1,&csource,NULL);
		glCompileShader(id);
		char error [1000];
		glGetShaderInfoLog(id,1000,NULL,error);
		print(error);
		return id;
	}
	/**
	   Create a shader program
	   @param a vector of shader ids.
	   @return the id of the program.
	*/
	static GLuint createShaderProgram(std::vector <GLuint> shaders)
	{
		GLuint programShader = glCreateProgram();
		for(unsigned int i =0; i< shaders.size();i++)
			glAttachShader(programShader,shaders[i]);
		glLinkProgram(programShader);
		return programShader;
	}

#endif /* SRC_SHADERUTILITY_H_ */
