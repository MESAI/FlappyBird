/*
 * Bird.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: MESAI
 */
#include "../include/Bird.h"


	Bird::Bird(Vec2 position, float radius)
	{
		this->position = position;
		this->acceleration = {0,-9.8};
		this->externalAcceleration = {0,0};
		this->velocity = {0,0};
		this->radius = radius;
		birdShaderProgramID = 0;
		// Create the bird Quad
		quad.bl.vect = (Vec2){-radius,radius};
		quad.br.vect = (Vec2){radius,radius};
		quad.tr.vect = (Vec2){radius,-radius};
		quad.tl.vect = (Vec2){-radius,-radius};
		quad.tl.texCoords = (Vec2){0,0};
		quad.tr.texCoords = (Vec2){1,0};
		quad.br.texCoords = (Vec2){1,1};
		quad.bl.texCoords = (Vec2){0,1};

	}

void Bird::draw(const float * projectionMartrix)
{
	glEnable(GL_TEXTURE);

	// setting up shader
	glUseProgram( birdShaderProgramID );

	// updating uniform values
	GLuint projectionIndex     = glGetUniformLocation(birdShaderProgramID, "projectionMatrix");
	glUniformMatrix4fv( projectionIndex, 1, GL_FALSE, (GLfloat*) projectionMartrix );

	// updating transformation Matrix
	GLuint transformationIndex      = glGetUniformLocation(birdShaderProgramID, "transformation");
	glUniformMatrix4fv(transformationIndex, 1, GL_FALSE, (GLfloat*) transfomation );

	// updating attribute values
	GLuint vPosition = glGetAttribLocation( birdShaderProgramID, "position" );
	GLuint vTextureCoord = glGetAttribLocation( birdShaderProgramID, "inputTextureCoordinate" );

	// beginning of arrays
	int kQuadSize  = sizeof(quad.bl);
	long offset = (long)&quad;
	int diff = offsetof(QuadVertex, vect);
	long vertices  =  offset+diff;
	diff = offsetof(QuadVertex, texCoords);
	long textureCoords  = offset+diff;

	// enabling vertex arrays
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*)vertices);
	glEnableVertexAttribArray(vTextureCoord);
	glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*)textureCoords);

	// drawing
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// exiting the drawing routine
	glDisableVertexAttribArray(vPosition);
	glDisableVertexAttribArray(vTextureCoord);
	glUseProgram(0);
	glDisable(GL_TEXTURE);

}

void Bird::clearForces()
{
	acceleration = {0,-9.8};
}

void Bird::updateTrasnformationMatrix()
{
	TranslationMatrix(transfomation,position.x, position.y, 0);
}

