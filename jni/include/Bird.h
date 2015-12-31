/*
 * bird.h
 *
 *  Created on: Dec 22, 2015
 *      Author: MESAI
 */

#ifndef INCLUDE_BIRD_H_
#define INCLUDE_BIRD_H_

#include "Utils.h"
#include <string>

class Bird {
public:
	// attributes
	float radius;
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	Vec2 externalAcceleration;
	float transfomation [16];
	Quad quad;

	//Shader
	GLuint birdShaderProgramID;

	/**
	  The constructor.
	  @param the 2d position.
	  @param the radius of the bird circle.
	*/
	Bird(Vec2 position, float radius);

	/**
	   The destructor.
	*/
	~Bird(){}

	/**
	   Clear the forces applied on the bird to calculate the forces for a new time step.
	*/
	void clearForces();
	/**
	   Update the transformation matrix based on the position of the bird.
	*/
	void updateTrasnformationMatrix();
	/**
	   draw the bird based on the projection matrix.
	   @param the projection matrix.
	*/
	void draw(const float * projectionMartrix);

};

#endif /* INCLUDE_BIRD_H_ */
