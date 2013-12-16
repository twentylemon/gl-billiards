/**
 * Entry point. Yay.
 *
 * @author Taras Mychaskiw, Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/
#include "main.h"
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

	int j;

    glBindTexture(GL_TEXTURE_2D, object->id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
		for (j = 0; j < object->polygons_qty; j++)
		{
			//----------------- FIRST VERTEX -----------------
		  //Normal coordinates of the first vertex
		  glNormal3f( object->normal[ object->polygon[j].a ]->getX(),
					  object->normal[ object->polygon[j].a ]->getY(),
					  object->normal[ object->polygon[j].a ]->getZ());
		  // Texture coordinates of the first vertex
		  glTexCoord2f( object->mapcoord[ object->polygon[j].a ].u,
						object->mapcoord[ object->polygon[j].a ].v);
		  // Coordinates of the first vertex
		  glVertex3f( object->vertex[ object->polygon[j].a ].x,
					  object->vertex[ object->polygon[j].a ].y,
					  object->vertex[ object->polygon[j].a ].z);

		  //----------------- SECOND VERTEX -----------------
		  //Normal coordinates of the second vertex
		  glNormal3f( object->normal[ object->polygon[j].b ]->getX(),
					  object->normal[ object->polygon[j].b ]->getY(),
					  object->normal[ object->polygon[j].b ]->getZ());
		  // Texture coordinates of the second vertex
		  glTexCoord2f( object->mapcoord[ object->polygon[j].b ].u,
						object->mapcoord[ object->polygon[j].b ].v);
		  // Coordinates of the second vertex
		  glVertex3f( object->vertex[ object->polygon[j].b ].x,
					  object->vertex[ object->polygon[j].b ].y,
					  object->vertex[ object->polygon[j].b ].z);

		  //----------------- THIRD VERTEX -----------------
		  //Normal coordinates of the third vertex
		  glNormal3f( object->normal[ object->polygon[j].c ]->getX(),
					  object->normal[ object->polygon[j].c ]->getY(),
					  object->normal[ object->polygon[j].c ]->getZ());
		  // Texture coordinates of the third vertex
		  glTexCoord2f( object->mapcoord[ object->polygon[j].c ].u,
						object->mapcoord[ object->polygon[j].c ].v);
		  // Coordinates of the Third vertex
		  glVertex3f( object->vertex[ object->polygon[j].c ].x,
					  object->vertex[ object->polygon[j].c ].y,
					  object->vertex[ object->polygon[j].c ].z);
		}
	glEnd();
}

/**
 * Main glut redraw function.
**/
void displayFunc(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	static double r = 0;
	glRotated(r, 1, 0, 0);
	r += 0.05;


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
    case ESC:
        break;
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
 * Entry point to the application. Defines the main window etc.
**/
int main(int argc, char** argv){
    glutInit(&argc, argv);

    init();

    glutDisplayFunc(displayFunc);
    glutIdleFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

	loadModels();

    glutMainLoop();
    return 0;
}
