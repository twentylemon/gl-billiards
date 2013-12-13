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

/**
 *	Loads all the models required for the scene using 3dsloader.h
 */
void loadModels(){
	
	tableEdges.loadObject("Objects/table_edges.3DS", "");
	tableBed.loadObject("Objects/table_bed.3DS", "Objects/textures/felt.bmp");
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
	gluLookAt(180, 20, 100, 0, 0, 30, 0, 0, 1);
   
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

    glutMainLoop();
    return 0;
}
