/**
 * Entry point. Yay.
 *
 * @author Taras Mychaskiw, Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/
#include "main.h"
#include "GL\glui.h"
Global global;

/**
 * Returns the amount of time in seconds between the two clocks.
 *
 * @param before the earlier time
 * @param after the last time
 * @return after - before in seconds
**/
double getTimeDiff(std::clock_t before, std::clock_t after){
    return (double)(after - before) / CLOCKS_PER_SEC;
}


/**
 * Takes in a vector and does a glTranslatef
 */
void glTranslatefv(Vector translate){
	glTranslatef(translate.getX(), translate.getY(), translate.getZ());
}

/**
 * Checks to see if balls are moving
 *
 * @returns true if balls are moving, false otherwise
 */
bool ballsMoving(){

	for(int i = 0; i <= 15; i++){
		if(global.balls[i]->isMoving()){
			return true;
		}
	}

	return false;
}


/**
 * Main glut redraw function.
**/
void displayFunc(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
	/* Translates for rotation and zoom of camera and draws table */
	if(global.tableZoom > 0.7)
		glTranslatef(global.tableZoom, 0, 0.7);
	else
		glTranslatef(global.tableZoom, 0, global.tableZoom);

	glRotatef(global.tableRotation->getX(), 1, 0, 0);
	glRotatef(global.tableRotation->getY(), 0, 1, 0);
	glRotatef(global.tableRotation->getZ(), 0, 0, 1);

    global.table->draw();
    for (unsigned int i = 0; i < global.balls.size(); i++){
        global.balls[i]->draw();
    }
	/* */


	/* Position the cue behind the cue ball */
	glPushMatrix();

	if(ballsMoving() == false){
		//if( player 1's turn )
			global.player1->getCue()->setPosition(global.balls[0]->getPosition());

		//else
		//	global.player2->getCue()->setPosition(global.balls[0]->getPosition());
	}
		
	glTranslatefv(global.player1->getCue()->getPosition());
	global.player1->drawCue();
	glPopMatrix();
	/* */


    static bool f = true;
    if (f){
        f = false;
        global.balls[0]->setPosition(Vector::add(global.balls[0]->getPosition(), Vector(0, -10 * 0.0254, 0)));
        global.balls[0]->setVelocity(10, 1, 0);
    }

    std::clock_t now = std::clock();
    if (!global.physics->update(global.balls, getTimeDiff(global.clock, now))){
        global.balls[0]->setVelocity(rand() % 4, rand() % 4, 0);
    }
    global.clock = now;
    
	/*
	//below draws spheres in the pockets
	double tableRailSize = 4 * 0.0254 / 2.0;
	double tablePlayWidth = 100.0 * 0.0254;    //100in (in m)
	double tablePlayHeight = 50.0 * 0.0254;    //50in (in m)
	double pocketSize = 4.8 * 0.0254 / 2.0;    //actually corner = 4.5, side = 5 in, close enough
	Vector pockets[6];
	pockets[0] = Vector(tablePlayWidth / 2.0 + tableRailSize, tablePlayHeight / 2.0 + tableRailSize, 0);    //top left
	pockets[1] = Vector(tablePlayWidth / 2.0 + tableRailSize, -tablePlayHeight / 2.0 - tableRailSize, 0);   //bottom left
	pockets[2] = Vector(0, -tablePlayHeight / 2.0 - tableRailSize, 0);                      //bottom middle
	pockets[3] = Vector(-tablePlayWidth / 2.0 - tableRailSize, -tablePlayHeight / 2.0 - tableRailSize, 0);  //bottom right
	pockets[4] = Vector(-tablePlayWidth / 2.0 - tableRailSize, tablePlayHeight / 2.0 + tableRailSize, 0);   //top right
	pockets[5] = Vector(0, tablePlayHeight / 2.0 + tableRailSize, 0);                       //top middle
	for (int i = 0; i < 6; i++){
		glPushMatrix();
		glTranslated(pockets[i].getX(), pockets[i].getY(), pockets[i].getZ() + 0.8);
		glutSolidSphere(pocketSize, 10, 10);
		glPopMatrix();
	}
	*/

	//Sleep(100);
	
    glPopMatrix();
	glutSwapBuffers();
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

	if(global.tableRotation->getY() >= 360)
		global.tableRotation->setY(global.tableRotation->getY() - 360);

	if(global.tableRotation->getY() < 0)
		global.tableRotation->setY(global.tableRotation->getY() + 360);

	if(global.tableRotation->getZ() >= 360)
		global.tableRotation->setZ(global.tableRotation->getZ() - 360);

	if(global.tableRotation->getZ() < 0)
		global.tableRotation->setZ(global.tableRotation->getZ() + 360);
	
	// >340 && <158

	//printf("%f, %f\n", global.tableRotation->getY(), global.tableRotation->getZ());

	global.tableRotation->add(0, global.mousePositionY - y, global.mousePositionX - x);
	
	global.mousePositionX = x;
	global.mousePositionY = y;
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

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		
	}
}

/**
 *	Freeglut mouse wheel callback function. Called when user scrolls
 *	the mouse wheel. Zooms in and out on the table
 *
 *	@param wheel mouse wheel number
 *	@param direction +/- 1 depending on direction of scroll
 *	@param int x mouse pointer x coord
 *	@param int y mouse pointer y coord
 */
void mouseWheelFunc(int wheel, int direction, int x, int y){

	printf("%f\n", global.tableZoom);

	if(direction > 0){
		//zoom in
		global.tableZoom += 0.10;
	} else {
		//zoom out
		global.tableZoom -= 0.10;
	}
}


/**
 *	Idle function for GLUI. Sets the main window if needed
**/
void glutIdleFunc()
{
	if (glutGetWindow() != global.glutWindow) 
		glutSetWindow(global.glutWindow);  

	glutPostRedisplay();
}

/**
 * Entry point to the application. Defines the main window etc.
**/
int main(int argc, char** argv){
    glutInit(&argc, argv);

	//GLUI_Master.set_glutIdleFunc(glutIdleFunc);

    init();

    glutDisplayFunc(displayFunc);
    glutIdleFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
	glutReshapeFunc(resizeWindow);
	glutMouseWheelFunc(mouseWheelFunc);


    glutMainLoop();
    return 0;
}
