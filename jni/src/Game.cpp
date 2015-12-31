#include "../include/Game.h"

// Attribute of the engine
static int screenWidth;
static int screenHeight;
static float projectionMatrix [16];
static Bird * bird = NULL;
static int numberOfObstacles = 3;
static Obstacle  * obstacles [3];
static int camera_startX;
static int gameStatus = 0;
static int demoAngle = 90;
static unsigned int obstaclesDeltaX = 500;
static unsigned int score = 0;
static unsigned int obstacleAheadX = 0;

// Shaders
static GLuint birdVertexShaderID;
static GLuint birdFragmentShaderID;
static GLuint birdShaderProgramID;
static GLuint obstacleVertexShaderID;
static GLuint obstacleFragmentShaderID;
static GLuint obstacleShaderProgramID;

void Game::onSurfaceCreated() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // initiate the bird shaders
    birdVertexShaderID = createShader(birdVertexShader,GL_VERTEX_SHADER);
    birdFragmentShaderID = createShader(birdFragmentShader,GL_FRAGMENT_SHADER);
    std::vector <GLuint> shaders;
    shaders.push_back(birdVertexShaderID);
    shaders.push_back(birdFragmentShaderID);
    birdShaderProgramID = createShaderProgram(shaders);
    shaders.clear();
    // initiate the obstacles shaders
    obstacleVertexShaderID = createShader(obstacleVertexShader,GL_VERTEX_SHADER);
    obstacleFragmentShaderID = createShader(obstacleFragmentShader,GL_FRAGMENT_SHADER);
    shaders.push_back(obstacleVertexShaderID);
    shaders.push_back(obstacleFragmentShaderID);
    obstacleShaderProgramID = createShaderProgram(shaders);
    shaders.clear();
}

void Game::onSurfaceChanged(int width, int height) {
	if(gameStatus == 0) { // sanity check
		screenWidth = width;
		screenHeight = height;
		glViewport(0, 0, screenWidth, screenHeight);
		// create a new game
		newGame();
	}
}

void Game::checkBoundaries()
{
	if(bird->position.y - bird->radius < -screenHeight/2.0)
	{
		bird->position.y = -screenHeight/2.0 + bird->radius;
		bird->velocity.y = 0;
		gameStatus = 2;
		Callbacks::gameOverCallBack();
	}

	if(bird->position.y + bird->radius > screenHeight/2.0)
	{
		bird->position.y = screenHeight/2.0 - bird->radius;
		bird->velocity.y = 0;
		gameStatus = 2;
		Callbacks::gameOverCallBack();
	}
}

void Game::checkCollision()
{
	for(int i = 0; i < numberOfObstacles; i++)
	{
		// get the nearest X for collision check
		int cX, cY;
		;
		if( bird->position.x < (obstacles[i]->center.x - OBSTACLE_WIDTH))
		{
			cX = obstacles[i]->center.x - OBSTACLE_WIDTH;
		}
		else if( bird->position.x > (obstacles[i]->center.x + OBSTACLE_WIDTH ))
		{
			cX = obstacles[i]->center.x + OBSTACLE_WIDTH;
		}
		else
		{
			cX = bird->position.x;
		}
		// get the nearest Y for collision check
		if(bird->position.y >  obstacles[i]->center.y)
		{
			if( bird->position.y < (obstacles[i]->center.y + OBSTACLE_OPENNING_RADIUS))
			{
				cY = obstacles[i]->center.y + OBSTACLE_OPENNING_RADIUS;
			}
			else if( bird->position.y > (float)screenHeight )
			{
				cY = (float)screenHeight;
			}
			else
			{
				cY = bird->position.y;
			}
		}else
		{
			if( bird->position.y > (obstacles[i]->center.y - OBSTACLE_OPENNING_RADIUS))
			{
				cY = obstacles[i]->center.y - OBSTACLE_OPENNING_RADIUS;
			}
			else if( bird->position.y < (float)-screenHeight)
			{
				cY = (float)-screenHeight;
			}
			else
			{
				cY = bird->position.y;
			}
		}
		// check for the distance from the circle center to the nearest point
		if( distanceSquared( bird->position.x, bird->position.y, cX, cY ) < bird->radius * bird->radius )
		{
		   //This box and the circle have collided
			gameStatus = 2;
			Callbacks::gameOverCallBack();
			break;
		}
	}
}

void Game::moveCamera()
{
	// Pan the camera to the right
	camera_startX = camera_startX + CAMERA_PAN;
}

void Game::updateCamera()
{
	// Get the Orthogonal Matrix for projection
	OrthoMatrix(projectionMatrix, camera_startX,camera_startX + screenWidth,-screenHeight/2.0,screenHeight/2.0,-5,5);
}

void Game::updateObstaclesProgressively()
{
	for(int i = 0; i < numberOfObstacles; i++ )
	{
		if((obstacles[i]->center.x + OBSTACLE_WIDTH) < camera_startX)
		{
			// clean out of screen obstacles
			delete obstacles[i];
			// insert a new obstacles
			float r = ((float) rand() / (RAND_MAX)) -0.5;
			Vec2 center = {(float)800 + obstaclesDeltaX,r*screenHeight/2};
			Obstacle * obstacle = new Obstacle(center,screenHeight);
			obstacle->obstacleShaderProgramID = obstacleShaderProgramID;
			obstacle->updateTrasnformationMatrix();
			obstacles[i] = obstacle;
			obstaclesDeltaX+=600;
		}
	}
}

void Game::updateTimeStep(float timeStep)
{
    bird->clearForces();
	bird->acceleration = {bird->acceleration.x+bird->externalAcceleration.x,bird->acceleration.y+bird->externalAcceleration.y};
	//Leap-Frog(ish) integration
	bird->velocity = {bird->velocity.x + bird->acceleration.x*timeStep,bird->velocity.y + bird->acceleration.y*timeStep};
	bird->position = {bird->position.x + bird->velocity.x*timeStep,bird->position.y + bird->velocity.y*timeStep};
	//check boundries
	checkBoundaries();
	//check collisions
	checkCollision();

}

void Game::updateScore()
{
	int min_distance = 10000;
	unsigned int newObstacle = 0;
	// Get the nearest Obstacle
	for(int i = 0; i<numberOfObstacles; i++)
	{
		if(	(bird->position.x < obstacles[i]->center.x)  &&
			(obstacles[i]->center.x - bird->position.x) < min_distance)
		{
			min_distance = obstacles[i]->center.x - bird->position.x;
			newObstacle = obstacles[i]->center.x;
		}
	}
	// Check if the obstacle is changed to update the score and notify the UI
	if (obstacleAheadX != newObstacle)
	{
		obstacleAheadX = newObstacle;
		score++;
		Callbacks::updateScoreCallBack(score);
	}
}

void Game::onDrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Start Menu
    if(gameStatus == 0) {
		updateCamera();
		updateScore();
		bird->position.y = 50 * cos((demoAngle*M_PI)/180.0);
		bird->updateTrasnformationMatrix();
		bird->draw(projectionMatrix);
		demoAngle+=5;
		demoAngle = demoAngle % 360;
    }
    // Gameplay
    if(gameStatus == 1) {
    	moveCamera();
		updateCamera();
		updateTimeStep(TIME_STEP);
		updateScore();
		updateObstaclesProgressively();
		bird->updateTrasnformationMatrix();
		bird->draw(projectionMatrix);
		for(int i = 0; i< numberOfObstacles; i++)
			obstacles[i]->draw(projectionMatrix);
    }
    // Freeze the Game
    if(gameStatus == 2) {
    	updateCamera();
    	bird->updateTrasnformationMatrix();
		bird->draw(projectionMatrix);
		for(int i = 0; i< numberOfObstacles; i++)
			obstacles[i]->draw(projectionMatrix);
    }
}

void Game::onTouchEventDown() {
	//if(bird->velocity.y<0) << Harder gameplay variation
		bird->velocity = {bird->velocity.x,0};
	bird->externalAcceleration = {0,19.6};
}

void Game::onTouchEventUp() {
	if(gameStatus == 0){
		gameStatus = 1;
	}
	if(gameStatus == 1) {
		bird->externalAcceleration = {0,0};
	}
}

void Game::newGame()
{
	// cleaning
	if(bird)
	{
		delete bird;
		for(int i = 0; i < numberOfObstacles; i++)
		{
			delete obstacles[i];
		}
	}
	// intialize
	camera_startX = -screenWidth/2.0;
	gameStatus = 0;
	score = -1;
	obstacleAheadX = -1;

	Vec2 position = {0,0};
	bird = new Bird(position,50);
	bird->velocity = {CAMERA_PAN/TIME_STEP,0};
	bird->birdShaderProgramID  = birdShaderProgramID;
	obstaclesDeltaX = 500;
	for(int i = 0; i< numberOfObstacles; i++)
	{
	   float r = ((float) rand() / (RAND_MAX)) -0.5;
	   Vec2 center = {(float)800 + obstaclesDeltaX,r*screenHeight/2};
	   Obstacle * obstacle = new Obstacle(center,screenHeight);
	   obstacle->obstacleShaderProgramID = obstacleShaderProgramID;
	   obstacle->updateTrasnformationMatrix();
	   obstacles[i] = obstacle;
	   obstaclesDeltaX+=500;
	}
}

void Game::clean()
{
	if(bird)
	{
		delete bird;
		for(int i = 0; i < numberOfObstacles; i++)
		{
			delete obstacles[i];
		}
	}
	glDetachShader(birdShaderProgramID, birdVertexShaderID);
	glDetachShader(birdShaderProgramID, birdFragmentShaderID);
	glDeleteShader(birdVertexShaderID);
	glDeleteShader(birdFragmentShaderID);

	glDetachShader(obstacleShaderProgramID, obstacleVertexShaderID);
	glDetachShader(obstacleShaderProgramID, obstacleFragmentShaderID);
	glDeleteShader(obstacleVertexShaderID);
	glDeleteShader(obstacleFragmentShaderID);

	glDeleteProgram(birdShaderProgramID);
	glDeleteProgram(obstacleShaderProgramID);

}
