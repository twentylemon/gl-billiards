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
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat specularLight[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat shininess[] = {50.0};
	GLfloat position[] = {0, 0, 100, 1.0};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
		
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
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
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
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
	initializeWindow();
}
