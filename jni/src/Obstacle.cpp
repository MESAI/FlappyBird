/*
 * Obstacle.cpp
 *
 *  Created on: Dec 27, 2015
 *      Author: MESAI
 */

#include "../include/Obstacle.h"

Obstacle::Obstacle(Vec2 center, int screenHeight)
{
	this->center = center;
	obstacleShaderProgramID = 0;

	// Create the upper half of the Obstacle
	quad1.bl.vect = (Vec2){-OBSTACLE_WIDTH, OBSTACLE_OPENNING_RADIUS};
	quad1.br.vect = (Vec2){OBSTACLE_WIDTH,  OBSTACLE_OPENNING_RADIUS};
	quad1.tr.vect = (Vec2){OBSTACLE_WIDTH,(float)screenHeight};
	quad1.tl.vect = (Vec2){-OBSTACLE_WIDTH,(float)screenHeight};
	// Create the lower half of the Obstacle
	quad2.bl.vect = (Vec2){-OBSTACLE_WIDTH,(float)-screenHeight};
	quad2.br.vect = (Vec2){OBSTACLE_WIDTH,(float)-screenHeight};
	quad2.tr.vect = (Vec2){OBSTACLE_WIDTH,- OBSTACLE_OPENNING_RADIUS};
	quad2.tl.vect = (Vec2){-OBSTACLE_WIDTH,- OBSTACLE_OPENNING_RADIUS};

}

void Obstacle::draw(const float * projectionMartrix)
{

	glEnable(GL_TEXTURE);

	// setting up shader
	glUseProgram( obstacleShaderProgramID );

	// updating uniform values
	GLuint projectionIndex     = glGetUniformLocation(obstacleShaderProgramID, "projectionMatrix");
	glUniformMatrix4fv( projectionIndex, 1, GL_FALSE, (GLfloat*) projectionMartrix );

	// updating attribute values
	GLuint vPosition = glGetAttribLocation( obstacleShaderProgramID, "position" );

	// updating transformation Matrix
	GLuint transformationIndex      = glGetUniformLocation(obstacleShaderProgramID, "transformation");
	glUniformMatrix4fv(transformationIndex, 1, GL_FALSE, (GLfloat*) transfomation );

	// QUAD 1
	// beginning of arrays
	int kQuadSize  = sizeof(quad1.bl);

	// enabling vertex arrays
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, kQuadSize, &quad1);

	// drawing
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// QUAD 2
	// enabling vertex arrays
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, kQuadSize, &quad2);

	// drawing
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// exiting the drawing routine
	glDisableVertexAttribArray(vPosition);
	glUseProgram(0);
	glDisable(GL_TEXTURE);

}

void Obstacle::updateTrasnformationMatrix()
{
	TranslationMatrix(transfomation,center.x, center.y, 0);
}
