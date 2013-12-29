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

	//if player has scratched, reset cue ball
	if (global.balls[0]->isSunk()){
		delete global.balls[0];
		global.balls[0] = new Ball(0);
        global.scratch = true;
	}
    else {
        global.scratch = false;
    }

	updatePlayerTextField();
    updateCue();
}


/**
 * Updates the cue position and rotation according to the UI.
**/
void updateCue(){
    double length = global.shotPowerSpinner->get_float_val();
    double theta = global.cueTranslate->get_z();
    double rads = theta * PI / 180.0;
    Vector position = Vector(cos(rads), sin(rads), 0);
    position.normalize(length);
    position.add(global.balls[0]->getPosition());

    global.players[global.turn].setCuePosition(position);
    global.players[global.turn].setCueRotation(Vector(0,0, theta));
}


/**
 * Takes the current players shot from where their cue is currently.
**/
void takeShot(){
    if (global.shooting){
        global.balls[0]->setVelocity(global.physics->cueShot(global.players[global.turn].getCue(), global.balls[0]));
        global.shooting = false;
    }
}


/**
 * Explicitly define the main window if it loses focus
 */
void idleFunc(){
	if (glutGetWindow() != global.glutWindow){
		glutSetWindow(global.glutWindow);
    }
	glutPostRedisplay();
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
        global.players[global.turn].drawCue();
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
