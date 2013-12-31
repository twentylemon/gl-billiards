/**
 * init.cpp
 * Contains all the initialization functions for use in the program.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-16
**/
#include "main.h"

/**
 * Initializes all scene lighting
 */
void initializeLighting(){
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float shininess[] = { 50.0f };
	float position[] = { 0, 0, 1, 0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}


/**
 *	Initializes the main display window. Sets up the viewport and camera,
 *	and initializes polygon and texture modes.
**/
void initializeWindow(){
    glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, global.windowWidth, global.windowHeight);  

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
	gluPerspective(PERSPECTIVE_FIELD_OF_VIEW_ANGLE, global.windowWidth/global.windowHeight, MIN_CLIPPING, MAX_CLIPPING); 
	gluLookAt(130 * 0.0254, 0, 50 * 0.0254, 0, 0, 0 * 0.0254, 0, 0, 1);
   
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
}


/**
 *	Sets window ratio when window is resized
 *
 *	@param width new window width
 *	@param height new window height
 */
void resizeWindow(int width, int height){
	GLUI_Master.auto_set_viewport();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	GLdouble ratio = (GLdouble)width/height;
	gluPerspective(PERSPECTIVE_FIELD_OF_VIEW_ANGLE, ratio, MIN_CLIPPING, MAX_CLIPPING); 

	glPopMatrix();
}


/**
 *	Initializes the materials used for objects
**/
void initializeMaterials(){
	float ambient[]= { 0.2f, 0.2f, 0.2f, 1 };
	float diffuse[]= { 1.0f, 1.0f, 1.0f, 1 };
	float specular[]= { 0.2f, 0.2f, 0.2f, 1 };
	float shininess[]= { 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess); 
}


/**
 * Creates all of the ball objects and the table.
 * A call to swapTurns() is still required after this is finished.
**/
void initializeGame(){
    for (int ballNum = 0; ballNum < 16; ballNum++){
        global.balls.push_back(new Ball(ballNum));
        global.prev.push_back(Ball(ballNum));
    }
	global.players[0] = Player(1);
    global.players[1] = Player(2);
    global.numPlayers = 2;
    global.turn = 1;
    global.other = 0;
    global.ballsMoving = false;
    global.typeSetThisTurn = false;
    global.firstBallHit = 0;
	global.gameOver = false;
    global.shots = -1;
    
    global.table = Table();
	global.cameraCenter = Vector();
    global.clock = std::clock();
    //a call to swapTurns() is required before play can begin!
}


/**
 * Restarts the game. Deletes all objects from memory preparing
 * for initializeGame() to be called
**/
void restartGame(){
	global.balls.clear();
	global.shootButton->set_name("Shoot");
	global.shotPowerSpinner->set_float_val(0.0);
    global.cueTranslate->set_z(180);

	resetCamera();
	resetZoom();

	initializeGame();
    swapTurns();
}


/**
 * Initializes the glut window and lighting, etc.
**/
void init(){
    srand((unsigned)time(NULL));
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	global.windowHeight = 600;
	global.windowWidth = 800;
	glutInitWindowSize(global.windowWidth, global.windowHeight);

    global.glutWindow = glutCreateWindow("gl-billiards");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
	initializeWindow();
	initializeLighting();
	initializeMaterials();
    initializeGame();
}
