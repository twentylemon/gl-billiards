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
 * @param position the position to check
 * @return true if the position is colliding with any ball other than the cue ball
**/
bool isColliding(Vector position){
    for (unsigned int i = 1; i < global.balls.size(); i++){
        if (global.balls[i]->getPosition().distance(position) < 4.0 * physics::ballRadiusSq){
            return true;
        }
    }
    return false;
}


/**
 * @param position the position to check
 * @return true if the position is within the legal (x,y) range for the ball in hand position
**/
bool legalRange(Vector position){
    return position.getX() >= CUE_BALL_XMIN && position.getX() <= CUE_BALL_XMAX &&
        position.getY() >= CUE_BALL_YMIN && position.getY() <= CUE_BALL_YMAX;
}


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
 * @return the rotation vector for drawing the table
**/
Vector getTableRotation(){
    return Vector(global.cameraTranslate->get_x(), global.cameraTranslate->get_y(), global.cameraTranslate->get_z());
}


/**
 * Updates the camera position, center of rotation etc.
**/
void updateCamera(){
    int type = global.cameraCenterType->get_int_val();
    if (type == CENTER_TYPE_ORIGIN){
        global.cameraCenter = Vector();
    }
    else if (type == CENTER_TYPE_FOLLOW){
        global.cameraCenter = Vector::scale(global.balls[global.follow]->getPosition(), -1.0);
    }
}


/**
 * Changes whose turn it is to shoot. Should only be called once
 * all balls have stopped moving.
**/
void swapTurns(){
    global.shooting = true;

    //check for fouls/scratch
    int playerBallType = global.players[global.turn].getBallType();
    int hitBallType = global.balls[global.firstBallHit]->getType();
    bool foul = hitBallType == BALL_TYPE_CUE || (hitBallType != playerBallType &&
        playerBallType != BALL_TYPE_NONE && !global.typeSetThisTurn && global.firstBallHit != 8);
    bool scratch = global.balls[0]->isSunk();

    //check for balls they sunk of their own type
    bool sunkMyOwn = false;
    for (unsigned int i = 0; i < global.balls.size(); i++){
        if (global.balls[i]->isSunk() && !global.prev[i].isSunk()){
            //this ball was sunk this shot
            if (playerBallType == global.balls[i]->getType()){
                sunkMyOwn = true;  //they sunk their own ball, huzzah
            }
        }
        //copy the state over to the new shot
        global.prev[i].copy(global.balls[i]);
    }

    if (!sunkMyOwn || scratch || foul){
        if (global.turn == 0){
            global.turn = 1;
            global.other = 0;
        }
        else {
            global.turn = 0;
            global.other = 1;
        }
    }

	//if player has scratched, reset cue ball, only if 8 ball is on the table
	if (scratch || foul){
		if (!global.balls[8]->isSunk()){
			global.balls[0]->setSunk(false);
			global.balls[0]->setPosition(global.balls[0]->getStartPosition());
		}
		global.scratch = true;
	}
    else {
        global.scratch = false;
    }

    global.typeSetThisTurn = false;
    global.firstBallHit = 0;
    global.shots++;
    global.msg.clear();
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
    global.players[global.turn].setCueRotation(Vector(0, 0, theta));
}


/**
 * Takes the current players shot from where their cue is currently.
 * If the user presses the shot button when the game is over, we restart the game.
**/
void takeShot(){
	if (global.gameOver){
		restartGame();
		return;
	}
	if (global.shotPowerSpinner->get_float_val() == 0.0){
		return;
    }
    if (global.shooting){
        global.balls[0]->setVelocity(physics::cueShot(global.players[global.turn].getCue(), global.balls[0]));
        global.shooting = false;
    }
}


/**
 * Checks to see if the current player has pocketed all balls of their type
 *
 * @returns true if the player has sunk all balls of their type, false otherwise
**/
bool allBallsPocketed(){
	if (global.players[global.turn].getBallType() == BALL_TYPE_SOLID){
		//check balls 1 - 7
		for (int i = 1; i <= 7; i++){
		    if (!global.balls[i]->isSunk()){
			    return false;
            }
        }
	}
    else if (global.players[global.turn].getBallType() == BALL_TYPE_STRIPE){
		//check balls 9 - 15
		for (int i = 9; i <= 15; i++){
		    if (!global.balls[i]->isSunk()){
			    return false;
            }
		}
	}
    else if (global.players[global.turn].getBallType() == BALL_TYPE_NONE){
        return false;
    }
	return true;
}


/**
 * Checks for any new balls that were sunk, and handles them accordingly.
**/
void updateSunkBalls(){
    if (global.balls[8]->isSunk()){
		global.gameOver = true;
		bool playerWon;	

		if (global.balls[0]->isSunk() || global.players[global.turn].getBallType() == BALL_TYPE_NONE){
			playerWon = false;  //automatic loss, dont need to check for pocketed balls
		}
        else {	
			playerWon = allBallsPocketed(); //checks to see if player has pocketed all balls of their type
		}
		if (playerWon){
			playerWins(global.turn);
		}
        else {
			playerWins(global.other);
		}
	}
    else {
        for (unsigned int ballNumber = 0; ballNumber <= 15; ballNumber++){
            if (global.balls[ballNumber]->isSunk() && !global.prev[ballNumber].isSunk()){
                std::string msg = "Ball " + std::to_string(ballNumber) + " Pocketed";
                if (ballNumber == 0){
                    msg = "Scratch";
				    //player scratched on 8 ball, other player wins
				    if (allBallsPocketed()){ 
					    global.gameOver = true;
					    playerWins(global.other);
				    }
                }
                if (std::find(global.msg.begin(), global.msg.end(), msg) == global.msg.end()){
                    global.msg.push_back(msg);
                }

                if (global.players[global.turn].getBallType() == BALL_TYPE_NONE){
                    global.typeSetThisTurn = true;
                    if (global.balls[ballNumber]->getType() == BALL_TYPE_SOLID){
			            global.players[global.turn].setBallType(BALL_TYPE_SOLID);
			            global.players[global.other].setBallType(BALL_TYPE_STRIPE);
		            }
                    else if (global.balls[ballNumber]->getType() == BALL_TYPE_STRIPE){
			            global.players[global.turn].setBallType(BALL_TYPE_STRIPE);
			            global.players[global.other].setBallType(BALL_TYPE_SOLID);
                    }
                }
            }
        }
        if (global.msg.size() > 0){
            global.shotInfoTextField->set_text(global.msg.back().data());
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

    updateCamera();
	
    global.table.draw(getTableRotation(), global.cameraCenter);
    for (unsigned int i = 0; i < global.balls.size(); i++){
        global.balls[i]->draw();
    }

    std::clock_t now = std::clock();
    if (global.shooting){
        global.players[global.turn].drawCue();
    }
    else {
        global.ballsMoving = physics::update(global.balls, getTimeDiff(global.clock, now), global.ballHit);
        if (global.firstBallHit == 0){
            global.firstBallHit = global.ballHit;
        }
        updateSunkBalls();
		if (!global.ballsMoving && !global.gameOver){
			swapTurns();
        }
    }
    global.clock = now;
	
    glPopMatrix();
	glutSwapBuffers();
}


/**
 * glut special keyboard function.
 *
 * @param key the character struck
 * @param x the x coord of where the mouse was when key was struck
 * @param y the y coord of where the mouse was when key was struck
**/
void keyboardFunc(int key, int x, int y){
    if (global.scratch || global.shots <= 0){
        Vector position = global.balls[0]->getPosition();
        switch (key){
        case GLUT_KEY_UP:
            do {
                position.add(CUE_BALL_STEP, 0, 0);
            } while (isColliding(position) && legalRange(position));
            break;
        case GLUT_KEY_DOWN:
            do {
                position.add(-CUE_BALL_STEP, 0, 0);
            } while (isColliding(position) && legalRange(position));
            break;
        case GLUT_KEY_LEFT:
            do {
                position.add(0, CUE_BALL_STEP, 0);
            } while (isColliding(position) && legalRange(position));
            break;
        case GLUT_KEY_RIGHT:
            do {
                position.add(0, -CUE_BALL_STEP, 0);
            } while (isColliding(position) && legalRange(position));
            break;
        }
        if (!isColliding(position) && legalRange(position)){
            global.balls[0]->setPosition(position);
            updateCue();
        }
    }
}


/**
 * Entry point to the application. Defines the main window etc.
**/
int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();

    glutDisplayFunc(displayFunc);
    glutSpecialFunc(keyboardFunc);

	GLUI_Master.set_glutReshapeFunc(resizeWindow);
	initializeGlui();

    swapTurns();

    glutMainLoop();
    return 0;
}
