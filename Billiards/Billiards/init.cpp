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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float shininess[] = { 50.0f };
	float position[] = { 0, 0, 1, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}


/**
 *	Initializes the main display window. Sets up the viewport and camera,
 *	and initializes polygon and texture modes.
 */
void initializeWindow(){
    glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, global.windowWidth, global.windowHeight);  

	//Projection mode
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
	gluPerspective(45.0f, global.windowWidth/global.windowHeight, 10.0f, 10000.0f); 
	gluLookAt(70, 0, 180, 0, 0, 30, 0, 0, 1);
   
    glEnable(GL_DEPTH_TEST); //enable z buffer
    glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
}


/**
 *	Initializes the materials used for objects
 */
void initializeMaterials(){
	float ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
	float diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
	float specular[]= { 0.2f, 0.2f, 0.2f, 0.0f };
	float shininess[]= { 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess); 
}


/**
 * Creates all of the ball objects and the table.
**/
void initializeGame(){
    for (int i = 0; i < 16; i++){
        global.balls.push_back(new Ball(i));
    }
    global.table = new Table();
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

    //glOrtho(-ORTHO_WIDTH, ORTHO_WIDTH, -ORTHO_HEIGHT, ORTHO_HEIGHT, -ORTHO_DEPTH, ORTHO_DEPTH);

	initializeLighting();
	initializeMaterials();
	initializeWindow();
    initializeGame();
}
