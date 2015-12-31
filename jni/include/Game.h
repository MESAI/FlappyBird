/*
 * game.h
 *
 *  Created on: Dec 22, 2015
 *      Author: MESAI
 */

#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <GLES2/gl2.h>
#include <string>
#include <vector>
#include "Logger.h"
#include "ShaderUtility.h"
#include "Bird.h"
#include "Obstacle.h"
#include "Callbacks.h"
#include "Utils.h"
#include <cstdlib>



#define CAMERA_PAN 6
#define TIME_STEP 0.3

class Game {

public:
	/**
	   An event indication that the GL surface is created
	*/
	static void onSurfaceCreated();
	/**
	    An event called whenever the surface dimensions are changed
	    in this game it is used to initialize the view-port and the game components

	    @param width of the surface
	    @param height of the surface
	*/
	static void onSurfaceChanged(int width, int height);
	/**
	    An Event called by the GL Surface renderer asking for drawing the objects on the screen
	    there is 3 modes here:
	    1: A demo mode waiting for the user to start playing.
	    2: The actual game play.
	    3: The game over mode, basically screen freeze.
	*/
	static void onDrawFrame();
	/**
	    An event listener to user finger when he presses on the screen
	*/
	static void onTouchEventDown();
	/**
	    An event listener to user finger when he remove his finger from the screen
	*/
	static void onTouchEventUp();
	/**
	   Initialize the Game Components (bird, obstacles and status variables).
	*/
	static void newGame();
	/**
	   Clean memory before exit.
	*/
	static void clean();
	/**
	    Update the camera location and move it to the right.
	*/
	static void moveCamera();
	/**
	    Update the obstacles by clearing any off passed obstacles and generation a
	    new one in circular form.
	    Like this the total number of obstacles in memory is always 3.
	    and the obstacles are generated on the fly dynamically.
	*/
	static void updateObstaclesProgressively();
	/**
	   Creates the projection matrix based on the update camera position.
	*/
	static void updateCamera();
	/**
	   	Integrate the acceleration and velocity of the bird to get the position,
	   	then check the boundaries and collision to determine is the game is over or not.
	   	The integrator used in this operation is a semi Leap-Frog integrator
	   	because the starting condition require the calculation of an offset of timeStep/2
	   	using euler or any other integrator first.
	   	but visually the we get is good and stable.

	    @param the integration time step.
	*/
	static void updateTimeStep(float timeStep);
	/**
	    Calculate the score and report it to the UI thread to announce it to the user
	*/
	static void updateScore();
	/**
	    Checks if the bird is between the floor and the ceiling of the game
		incase of any violation the game is ended and the player loses.
	*/
	static void checkBoundaries();
	/**
	    Check if the bird have hit any of the obstacles on its way or not
	    in case of collision the game is ended and the player loses.
	*/
	static void checkCollision();
};
#endif /* INCLUDE_GAME_H_ */
