/*
 * utils.h
 *
 *  Created on: Dec 26, 2015
 *      Author: MESAI
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLES2/gl2.h>
#include "Logger.h"

// Define a simple 2D vector
typedef struct Vec2 {
    float x,y;
} Vec2;

// Define a simple 4-byte color
typedef struct Color4B {
    GLbyte r,g,b,a;
}Color4B;

// Define a suitable quad vertex with a color and tex coords.
typedef struct QuadVertex {
    Vec2 vect;              // 8 bytes
    Color4B color;          // 4 bytes
    Vec2 texCoords;         // 8 bytes
} QuadVertex;

typedef struct Quad {
    QuadVertex tl;
    QuadVertex bl;
    QuadVertex tr;
    QuadVertex br;
} Quad;

/**
   Create a Ortho matrix using the screen params.
   @param projection matrix [out].
   @param left value of the screen.
   @param right value of the screen.
   @param bottom value of the screen.
   @param top value of the screen.
   @param near value of the Z plane.
   @param far value of the Z plane.
*/
static void OrthoMatrix(float* projectionMatrix,float left, float right, float bottom, float top, float near, float far)
{
	glm::mat4 matrix = glm::ortho(left,right,bottom,top,near,far);
	for(int i = 0; i< 4; i++)
		for(int j = 0; j< 4; j++)
			projectionMatrix[i*4+j] = matrix[i][j];

}

/**
   Create a translation matrix using x, y, z deltas.
   @param the translation matrix [out]
   @param change in x
   @param change in y
   @param change in z
*/
static void TranslationMatrix(float* translationMatrix,float x, float y, float z)
{
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f),glm::vec3(x,y,z));
	for(int i = 0; i< 4; i++)
		for(int j = 0; j< 4; j++)
			translationMatrix[i*4+j] = matrix[i][j];

}

/**
   Get the euclidean distance between to points.
   @param the tanstalation matrix [out]
   @param  x1
   @param  y1
   @param  x2
   @param  y2
   @return the distance.
*/
static double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

#endif /* INCLUDE_UTILS_H_ */
