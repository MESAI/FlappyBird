/*
 * obstacle.h
 *
 *  Created on: Dec 22, 2015
 *      Author: MESAI
 */

#ifndef INCLUDE_OBSTACLE_H_
#define INCLUDE_OBSTACLE_H_

#define OBSTACLE_WIDTH 100
#define OBSTACLE_OPENNING_RADIUS 200

#include "Utils.h"
#include <vector>

class Obstacle
{

public:
	//attributes
	Vec2 center;
	Quad quad1;
	Quad quad2;
	float transfomation [16];

	// shader
	GLuint obstacleShaderProgramID;

	/**
	  The constructor.
	  @param position of the obstacle.
	  @param the viewport height.
	*/
	Obstacle(Vec2 center, int screenHeight);

	/**
	  The destructor.
	*/
	~Obstacle() { }
	/**
	   Update the transformation matrix based on the position of the obstacle.
	*/
	void updateTrasnformationMatrix();
	/**
	   draw the obstacle based on the projection matrix.
	   @param the projection matrix.
	*/
	void draw(const float * projectionMartrix);


};



#endif /* INCLUDE_OBSTACLE_H_ */
