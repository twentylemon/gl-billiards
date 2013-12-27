/**
 * Entry point. Yay.
 *
 * @author Taras Mychaskiw, Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/
#include "main.h"
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
 * @return a random number in range [0,1)
**/
double random(){
    return (double)rand() / (double)RAND_MAX;
}


/**
 * Changes whose turn it is to shoot. Should only be called once
 * all balls have stopped moving.
**/
void swapTurns(){
    global.shooting = true;
    if (global.turn == 0){
        global.turn = 1;
        global.other = 0;
    }
    else {
        global.turn = 0;
        global.other = 1;
    }
    global.players[global.turn].setCuePosition(global.balls[0]->getPosition());
}


/**
 * Takes the current players shot from where their cue is currently.
**/
void takeShot(){
    global.balls[0]->setVelocity(global.physics->cueShot(global.players[global.turn].getCue(), global.balls[0]));
    global.shooting = false;
}


/**
 * Explicitly define the main window if it loses focus
 */
void idleFunc(){
	if (glutGetWindow() != global.glutWindow) 
		glutSetWindow(global.glutWindow);  

	glutPostRedisplay();
}


/**
 * Main glut redraw function.
**/
void displayFunc(){
    
    static bool f = true;
    if (f){ //make the break shot
        f = false;
        global.balls[0]->setPosition(Vector::add(global.balls[0]->getPosition(), Vector(0, -10 * 0.0254, 0)));
        global.players[global.turn].addCuePosition(Vector(-1.5 + random(), -0.5 + random(), 0));
        takeShot();
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
	/* Translates for rotation and zoom of camera and draws table */
	if (global.tableZoom > 0.7){
		glTranslatef(global.tableZoom, 0, 0.7);
    }
	else {
		glTranslatef(global.tableZoom, 0, global.tableZoom);
    }
	glRotatef(global.tableRotation.getX(), 1, 0, 0);
	glRotatef(global.tableRotation.getY(), 0, 1, 0);
	glRotatef(global.tableRotation.getZ(), 0, 0, 1);

    global.table.draw();
    for (unsigned int i = 0; i < global.balls.size(); i++){
        global.balls[i]->draw();
    }

    std::clock_t now = std::clock();
    if (global.shooting){
        global.players[global.turn].addCuePosition(Vector(random(), random(), 0));
        global.players[global.turn].drawCue();
        takeShot();
    }
    else {
        global.ballsMoving = global.physics->update(global.balls, getTimeDiff(global.clock, now));

        if (!global.ballsMoving){
            swapTurns();
        }
    }
    global.clock = now;
	
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
	if (global.tableRotation.getY() >= 360){
		global.tableRotation.setY(global.tableRotation.getY() - 360);
    }
	else if (global.tableRotation.getY() < 0){
		global.tableRotation.setY(global.tableRotation.getY() + 360);
    }
	if (global.tableRotation.getZ() >= 360){
		global.tableRotation.setZ(global.tableRotation.getZ() - 360);
    }
	else if (global.tableRotation.getZ() < 0){
		global.tableRotation.setZ(global.tableRotation.getZ() + 360);
    }
	// >340 && <158

	global.tableRotation.add(0, global.mousePositionY - y, global.mousePositionX - x);
	
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

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
    std::cerr << global.tableZoom << std::endl;

	if (direction > 0){
		global.tableZoom += 0.10;   //zoom in
	}
    else {
		global.tableZoom -= 0.10;   //zoom out
	}
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
	//glutMouseWheelFunc(mouseWheelFunc);
    glutMotionFunc(motionFunc);
	GLUI_Master.set_glutReshapeFunc(resizeWindow);

	initializeGlui();

    glutMainLoop();
    return 0;
}
