/**
 * Entry point. Yay.
 *
 * @author Taras Mychaskiw, Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/

/**********************************************************
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 *			The contents of drawObject() was used from these examples 
			to draw a model to the window
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * Include File: 3dsloader.cpp
 ***********************************************************/


//REMOVE THIS AND FIX DEPRECATED FILE IN.... LATER...
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
/////////

#include <stdio.h>
#include <windows.h>
#include "main.h"
#include "ModelLoader.h"
#include "Model.h"

Global global;

Model tableBed;
Model tableEdges;
Model balls[15]; //all of the balls from 1-15
Model cueBall;

/**
 *	Loads all the models required for the scene using 3dsloader.h
 */
void loadModels(){
	
	tableEdges.loadObject("Objects/table_edges.3DS", "Objects/textures/crate.bmp");
	tableBed.loadObject("Objects/table_bed.3DS", "Objects/textures/felt.bmp");

	balls[0].loadObject("Objects/ball.3DS", "Objects/textures/ball01.bmp"); //ball 1
	balls[1].loadObject("Objects/ball.3DS", "Objects/textures/ball02.bmp"); //ball 2
	balls[2].loadObject("Objects/ball.3DS", "Objects/textures/ball03.bmp"); //ball 3
	balls[3].loadObject("Objects/ball.3DS", "Objects/textures/ball04.bmp"); //ball 4
	balls[4].loadObject("Objects/ball.3DS", "Objects/textures/ball05.bmp"); //ball 5
	balls[5].loadObject("Objects/ball.3DS", "Objects/textures/ball06.bmp"); //ball 6
	balls[6].loadObject("Objects/ball.3DS", "Objects/textures/ball07.bmp"); //ball 7
	balls[7].loadObject("Objects/ball.3DS", "Objects/textures/ball08.bmp"); //ball 8
	balls[8].loadObject("Objects/ball.3DS", "Objects/textures/ball09.bmp"); //ball 9
	balls[9].loadObject("Objects/ball.3DS", "Objects/textures/ball10.bmp"); //ball 10
	balls[10].loadObject("Objects/ball.3DS", "Objects/textures/ball11.bmp"); //ball 11
	balls[11].loadObject("Objects/ball.3DS", "Objects/textures/ball12.bmp"); //ball 12
	balls[12].loadObject("Objects/ball.3DS", "Objects/textures/ball13.bmp"); //ball 13
	balls[13].loadObject("Objects/ball.3DS", "Objects/textures/ball14.bmp"); //ball 14
	balls[14].loadObject("Objects/ball.3DS", "Objects/textures/ball15.bmp"); //ball 15

	cueBall.loadObject("Objects/ball.3DS", "Objects/textures/cue_ball.bmp");

}


/**
 *	Draws a loaded 3ds object
 *
 *	@param object the object to be drawn to the window
 */
void drawObject(obj_type* object){

	int l_index;

    glBindTexture(GL_TEXTURE_2D, (*object).id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
		for (l_index=0;l_index < (*object).polygons_qty;l_index++)
		{
			//----------------- FIRST VERTEX -----------------
			// Texture coordinates of the first vertex
			glTexCoord2f( (*object).mapcoord[ (*object).polygon[l_index].a ].u,
						  (*object).mapcoord[ (*object).polygon[l_index].a ].v);
			// Coordinates of the first vertex
			glVertex3f( (*object).vertex[ (*object).polygon[l_index].a ].x,
						(*object).vertex[ (*object).polygon[l_index].a ].y,
						(*object).vertex[ (*object).polygon[l_index].a ].z); //Vertex definition

			//----------------- SECOND VERTEX -----------------
			// Texture coordinates of the second vertex
			glTexCoord2f( (*object).mapcoord[ (*object).polygon[l_index].b ].u,
						  (*object).mapcoord[ (*object).polygon[l_index].b ].v);
			// Coordinates of the second vertex
			glVertex3f( (*object).vertex[ (*object).polygon[l_index].b ].x,
						(*object).vertex[ (*object).polygon[l_index].b ].y,
						(*object).vertex[ (*object).polygon[l_index].b ].z);
        
			//----------------- THIRD VERTEX -----------------
			// Texture coordinates of the third vertex
			glTexCoord2f( (*object).mapcoord[ (*object).polygon[l_index].c ].u,
						  (*object).mapcoord[ (*object).polygon[l_index].c ].v);
			// Coordinates of the Third vertex
			glVertex3f( (*object).vertex[ (*object).polygon[l_index].c ].x,
						(*object).vertex[ (*object).polygon[l_index].c ].y,
						(*object).vertex[ (*object).polygon[l_index].c ].z);
		}
	glEnd();
}

/**
 * Main glut redraw function.
**/
void displayFunc(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();


	drawObject(tableBed.getModel());
	drawObject(tableEdges.getModel());

	drawObject(balls[0].getModel());

	glTranslatef(10, 10, 30);
	drawObject(balls[13].getModel()); //ball 14

	
    glPopMatrix();
	glutSwapBuffers();
}

/**
 * Called when window is resized
 *
 * @param width new window width
 * @param height new window height
**/
void resizeFunc(int width, int height){
	global.windowHeight = height;
	global.windowWidth = width;
}


/**
 * glut keyboard function.
 *
 * @param key the character struck
 * @param x the x coord of where the mouse was when key was struck
 * @param y the y coord of where the mouse was when key was struck
**/
void keyboardFunc(unsigned char key, int x, int y){
    switch (key){
    case ESC: case 'q': case 'Q':
        return glutDestroyWindow(global.glutWindow);
    }
}


/**
 * glut mouse move function.
 *
 * @param x the x coord of where the mouse event occurred
 * @param y the y coord of where the mouse event occurred
**/
void motionFunc(int x, int y){
}


/**
 * glut mouse click function.
 *
 * @param button the mouse button clicked
 * @param state the state the button is in (up,down)
 * @param x the x coord of where the mouse event occurred
 * @param y the y coord of where the mouse event occurred
**/
void mouseFunc(int button, int state, int x, int y){
}


/**
 * Initializes all scene lighting
 *
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
 * Entry point to the application. Defines the main window etc.
**/
int main(int argc, char** argv){
    srand((unsigned)time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	global.windowHeight = 600;
	global.windowWidth = 800;
	glutInitWindowSize(global.windowWidth, global.windowHeight);

    global.glutWindow = glutCreateWindow("gl-billiards");
    //glutFullScreen();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glOrtho(-ORTHO_WIDTH, ORTHO_WIDTH, -ORTHO_HEIGHT, ORTHO_HEIGHT, -ORTHO_DEPTH, ORTHO_DEPTH);

    glutDisplayFunc(displayFunc);
    //glutIdleFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

	initializeWindow();
	loadModels();
	initializeLighting();

    glutMainLoop();
    return 0;
}
