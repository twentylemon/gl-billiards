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
        global.balls[0]->setSunk(false);
        global.balls[0]->setPosition(global.balls[0]->getStartPosition());
        global.scratch = true;
	}
    else {
        global.scratch = false;
    }

	updatePlayerTextField();
	global.shotInfoTextField->set_text("");
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
        global.balls[0]->setVelocity(physics::cueShot(global.players[global.turn].getCue(), global.balls[0]));
        global.shooting = false;
    }
}


/**
 * Checks for any new balls that were sunk, and handles them accordingly.
**/
void updateSunkBalls(){
	if (global.balls[0]->isSunk()){
		global.shotInfoTextField->set_text("Scratch");
	}
    else if (global.balls[8]->isSunk()){
        // TODO handle win/loss
	}

    //i = ballNumber
    for (unsigned int i = 1; i <= 15; i++){
        if (!global.sinkState[i] && global.balls[i]->isSunk()){
            global.sinkState[i] = true;
		    std::string str = "ball " + std::to_string(i) + " pocketed";
		    global.shotInfoTextField->set_text(str.data());

            if (i >= 1 && i <= 7 && global.players[global.turn].getBallType() == BALL_TYPE_NONE){
			    global.players[global.turn].setBallType(BALL_TYPE_SOLID);
			    global.players[global.other].setBallType(BALL_TYPE_STRIPE);
		    }
            else if (i >= 9 && i <= 15 && global.players[global.turn].getBallType() == BALL_TYPE_NONE){
			    global.players[global.turn].setBallType(BALL_TYPE_STRIPE);
			    global.players[global.other].setBallType(BALL_TYPE_SOLID);
            }
        }
    }
}


/**
 * Explicitly define the main window if it loses focus.
**/
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

    global.table.draw();
    for (unsigned int i = 0; i < global.balls.size(); i++){
        global.balls[i]->draw();
    }

    std::clock_t now = std::clock();
    if (global.shooting){
        global.players[global.turn].drawCue();
    }
    else {
        global.ballsMoving = physics::update(global.balls, getTimeDiff(global.clock, now));
        updateSunkBalls();
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
    Vector rotation = global.table.getRotation();
    /*
    if (rotation.getY() >= 360){
        rotation.setY(rotation.getY() - 360);
    }
	else if (rotation.getY() < 0){
        rotation.setY(rotation.getY() + 360);
    }
    if (rotation.getZ() >= 360){
        rotation.setZ(rotation.getZ() - 360);
    }
	else if (rotation.getZ() < 0){
        rotation.setZ(rotation.getZ() + 360);
    }
    */
    rotation.add(0, global.mousePositionY - y, global.mousePositionX - x);
    global.table.setRotation(rotation);
	
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
